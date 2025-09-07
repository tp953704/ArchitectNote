# LLM 基礎學習筆記 - 從 Ollama 到 LangChain

## 第一部分：Ollama - 你的本地 LLM 實驗室

`[+]` **核心概念**: Ollama 是一個讓你能在個人電腦上輕鬆運行、管理、並與大型語言模型（LLM）互動的工具。它將複雜的設定流程打包，讓你用幾個簡單的指令就能啟動並測試各種開源 LLM。

> **[大師心法]**
> 把 Ollama 當作「LLM 的 Docker」。需要新模型就 `pull`，想聊天就 `run`，不再需要就 `rm`。它將複雜的模型設定流程全部打包，讓你專注於與模型互動。

---

## 第二部分：LangChain 核心概念

`[+]` **核心概念**: LangChain 是一個「LLM 應用程式開發框架」。它提供了一系列標準化的元件（Components），以及一套名為 **LCEL** 的語言，讓你像組合樂高積木一樣，將這些元件串連起來，快速搭建功能強大的 AI 應用。

### 2.1. 三大基礎元件 (The Primitives)

*   **Models (模型)**: 應用的「大腦」。
*   **Prompts (提示)**: 給模型的「任務說明書」。
*   **Output Parsers (輸出解析器)**: 模型的「格式整理師」。

---

## 第三部分：對話歷史管理 (Chat History)

`[+]` **核心概念**: 為了讓 LLM 能夠理解對話的上下文，我們需要一個機制來儲存和傳遞對話歷史。LangChain 提供了從手動到自動的完整解決方案。

### 3.1. `ChatMessageHistory` (記憶體儲存)

在記憶體中儲存訊息的基礎類別，適合快速測試。

### 3.2. `SQLChatMessageHistory` (持久化儲存)

將對話紀錄存入 SQL 資料庫的工具，適合需要長期保存對話的應用程式。

> **[大師心法]**
> `session_id` 是識別不同對話的「鑰匙」。使用相同的 `session_id` 就能讀取到過去的所有對話，這就是實現「記憶」功能的關鍵！

### 3.3. 在 Chain 中手動管理歷史

這個模式的核心在於「手動管理」。每次對話後，我們需要自己將新的問答加入到 `chat_history` 物件中，然後在下一次呼叫時再把它傳進去。

### 3.4. `[+]` RunnableWithMessageHistory (自動化歷史管理)

`[+]` **核心概念**: `RunnableWithMessageHistory` 是一個強大的「包裝器」，它能自動處理對話歷史的讀取和儲存，讓你不再需要手動管理 `chat_history` 物件。

**運作原理**: 
1.  你提供一個核心的 `chain`。
2.  你提供一個 `get_session_history` 函數，這個函數會根據傳入的 `session_id` 回傳對應的歷史紀錄物件（可以是記憶體的，也可以是 SQL 的）。
3.  `RunnableWithMessageHistory` 會在執行前，自動根據 `session_id` 呼叫你的函數來「讀取」歷史紀錄，並將其填入 Prompt。
4.  在執行後，它會自動將新的問答「儲存」到同一個歷史紀錄物件中。

```python
from langchain_core.runnables.history import RunnableWithMessageHistory
from langchain_community.chat_message_histories import ChatMessageHistory
from langchain_community.chat_models import ChatOllama
from langchain_core.prompts import ChatPromptTemplate, MessagesPlaceholder

# 1. 核心 Chain (不包含歷史管理邏輯)
llm = ChatOllama(model="llama3")
prompt = ChatPromptTemplate.from_messages([
    ("system", "You are a helpful assistant."),
    MessagesPlaceholder(variable_name="history"),
    ("human", "{input}"),
])
chain = prompt | llm

# 2. 建立一個儲存所有對話歷史的 "資料庫" (此處用字典模擬)
store = {}

# 3. 建立 get_session_history 函數
def get_session_history(session_id: str) -> ChatMessageHistory:
    if session_id not in store:
        store[session_id] = ChatMessageHistory()
    return store[session_id]

# 4. 使用 RunnableWithMessageHistory 包裝 Chain
with_message_history = RunnableWithMessageHistory(
    chain,
    get_session_history,
    input_messages_key="input",
    history_messages_key="history",
)

# 5. 執行 Chain，只需傳入 session_id
config = {"configurable": {"session_id": "user_abc"}}

# 第一次對話
response = with_message_history.invoke({"input": "你好，我叫 Bob"}, config=config)
print(f"AI: {response.content}")

# 第二次對話 (無需手動傳遞歷史)
response = with_message_history.invoke({"input": "我叫什麼名字？"}, config=config)
print(f"AI: {response.content}")
# >> AI: 你好 Bob！很高興認識你。你剛才告訴我你叫 Bob。

# 查看儲存的歷史
print(store["user_abc"].messages)
```

> **[大師心法]**
> `RunnableWithMessageHistory` 是建構有狀態 (Stateful) 聊天機器人的標準做法。它將歷史管理的複雜性完全封裝起來，讓你的核心邏輯可以保持乾淨。你只需要定義好「如何存取歷史紀錄」(`get_session_history`)，剩下的交給它就好了。這才是真正能應用於生產環境的模式。

---

## 第四部分：進階應用 - RAG (檢索增強生成)

`[+]` **核心概念**: RAG (Retrieval-Augmented Generation) 是一種讓 LLM 能夠存取外部知識庫的技術。它「檢索 (Retrieve)」相關資訊，然後將這些資訊「增強 (Augment)」到 Prompt 中，讓 LLM 能根據這些額外資訊來「生成 (Generate)」更準確、更具體的回答。

> **[大師心法]**
> RAG 就像是給 LLM 一本「開卷考試」的參考書。它不用只靠自己腦中的知識，而是可以先查書（檢索），再根據書本內容來回答問題，大大提升了回答的準確性和時效性。

---

## 第五部分：LangSmith - 你的 LLM 開發儀表板

`[+]` **核心概念**: LangSmith 是一個專為 LLM 應用開發設計的平台，它能讓你追蹤、監控、評估和除錯你的 LangChain 應用。

> **[大師心法]**
> 開發 LLM 應用就像在黑盒子裡摸索。LangSmith 給了你一雙「透視眼鏡」，讓你清楚看見 Prompt、模型輸出、Token 消耗、延遲等所有細節，不再盲目開發。**強烈建議所有 LangChain 開發者從第一天就開始使用 LangSmith。**
