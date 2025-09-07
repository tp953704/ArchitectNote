# LangChain 對話歷史管理深度解析

## 前言：為何對話歷史至關重要？

一個無法記住對話的聊天機器人，就像一個只有三秒記憶的訪客，每次對話都是一次全新的開始。為了打造真正有智慧、能理解上下文的對話式 AI，我們必須賦予它「記憶」。在 LangChain 中，這個記憶機制就是「對話歷史管理」(Chat History Management)。

本筆記將從最基礎的記憶體儲存，一路深入到生產環境中常用的自動化、持久化儲存方案。

---

## 第一章：記憶的基礎 - `ChatMessageHistory`

`ChatMessageHistory` 是 LangChain 中最基本的記憶體類別。它就像一張暫時的便條紙，在程式運行的當下，幫你記住對話內容。

### 1.1 核心操作

它的操作非常直觀：使用 `add_message()` 來新增訊息，並透過 `.messages` 屬性來讀取所有訊息。

```python
from langchain_core.chat_history import ChatMessageHistory
from langchain_core.messages import HumanMessage, AIMessage

# 初始化一個空的歷史紀錄物件
memory_history = ChatMessageHistory()

# 新增一則使用者的訊息
memory_history.add_message(HumanMessage(content="你好！我對學習 LangChain 很感興趣。"))

# 新增一則 AI 的回覆
memory_history.add_message(AIMessage(content="你好！很高興聽到你對 LangChain 感興趣。"))

# 查看當前的所有訊息
print(memory_history.messages)
# >> [HumanMessage(content='你好！我對學習 LangChain 很感興趣。'), AIMessage(content='你好！很高興聽到你對 LangChain 感興趣。')]
```

> **[大師心法]**
> `ChatMessageHistory` 是最純粹的記憶體實作，非常適合快速原型設計和功能測試。但它的致命缺點是「健忘」——程式一旦停止，所有記憶都會煙消雲散。因此，對於任何需要長期記憶的應用，我們都需要更強大的工具。

---

## 第二章：讓記憶永存 - `SQLChatMessageHistory`

當我們需要讓聊天機器人記住昨天的對話，甚至上週的對話時，就需要將記憶「持久化」。`SQLChatMessageHistory` 就是為此而生，它將對話紀錄安全地存放在 SQL 資料庫中。

### 2.1 核心概念：`session_id`

在多人使用的聊天應用中，我們如何區分張三和李四的對話？答案就是 `session_id`。它是一個獨一無二的字串，用來標記每一段獨立的對話。

### 2.2 核心操作

使用時，除了提供資料庫的連接資訊，最重要的就是指定 `session_id`。

```python
from langchain_community.chat_message_histories import SQLChatMessageHistory

# 為這段對話定義一個唯一的 session_id
session_id = "user_123_conv_456"

# 設定資料庫連接字串 (這裡會在本機建立一個名為 chat_history.db 的 SQLite 檔案)
connection_string = "sqlite:///chat_history.db"

# 初始化 SQL 歷史紀錄物件
sql_history = SQLChatMessageHistory(
    session_id=session_id, 
    connection_string=connection_string
)

# 新增的訊息會被自動寫入資料庫中與 session_id 關聯的表格
sql_history.add_message(HumanMessage(content="我可以用 SQL 來儲存對話嗎？"))
sql_history.add_message(AIMessage(content="是的，你可以使用 SQLChatMessageHistory。它會自動處理資料庫的讀寫。"))

# 讀取時，它會自動從資料庫中撈取這個 session_id 的所有歷史訊息
print(sql_history.messages)
```

> **[大師心法]**
> `session_id` 是你通往特定對話記憶的「鑰匙」。在真實應用中，你通常會將 `session_id` 與使用者的登入 ID 或其他唯一識別碼綁定。當使用者再次上線時，你就能用同一把鑰匙，打開他塵封的對話紀錄，實現無縫接軌的對話體驗。

---

## 第三章：終極解決方案 - `RunnableWithMessageHistory`

手動管理歷史紀錄（每次對話後 `add_message`，每次對話前再傳入 `messages`）既繁瑣又容易出錯。`RunnableWithMessageHistory` 是一個強大的「包裝器」，它將這個過程完全自動化，是建構生產級聊天應用的不二之-選。

### 3.1 運作原理

它像一個聰明的管家，在你和你的核心 Chain 之間工作：
1.  **執行前**: 自動根據 `session_id` 去你的「記憶倉庫」中「讀取」歷史紀錄。
2.  **執行後**: 自動將最新的「使用者提問」和「AI 回覆」打包，「儲存」回你的「記憶倉庫」。

你唯一要做的，就是告訴這位管家，你的「記憶倉庫」在哪裡，以及如何根據 `session_id` 存取它。

### 3.2 核心操作

```python
from langchain_core.runnables.history import RunnableWithMessageHistory
from langchain_community.chat_message_histories import ChatMessageHistory
from langchain_community.chat_models import ChatOllama
from langchain_core.prompts import ChatPromptTemplate, MessagesPlaceholder

# 1. 你的核心 Chain (它完全不知道歷史管理的存在，非常乾淨)
llm = ChatOllama(model="llama3")
prompt = ChatPromptTemplate.from_messages([
    ("system", "You are a helpful assistant."),
    MessagesPlaceholder(variable_name="history"), # 為歷史紀錄預留位置
    ("human", "{input}"),
])
chain = prompt | llm

# 2. 你的「記憶倉庫」(此處用字典模擬，也可以換成 Redis 或其他資料庫)
store = {}

# 3. 告訴管家如何存取倉庫的「說明書」(get_session_history 函數)
def get_session_history(session_id: str) -> ChatMessageHistory:
    if session_id not in store:
        store[session_id] = ChatMessageHistory() # 如果是新使用者，就給他一個新的記憶便條紙
    return store[session_id] # 回傳這位使用者的專屬便條紙

# 4. 聘請管家，讓他管理你的 Chain
with_message_history = RunnableWithMessageHistory(
    chain, # 你要他管理的核心業務
    get_session_history, # 他存取記憶的說明書
    input_messages_key="input", # 告訴他使用者的輸入在哪個欄位
    history_messages_key="history", # 告訴他歷史紀錄要放在 prompt 的哪個位置
)

# 5. 開始對話！
# 你只需要在 config 中提供 session_id，管家就會處理一切
config = {"configurable": {"session_id": "user_xyz"}}

response = with_message_history.invoke({"input": "你好，我叫 David"}, config=config)
print(f"AI: {response.content}")

# 第二次對話，無需任何手動操作
response = with_message_history.invoke({"input": "我叫什麼名字？"}, config=config)
print(f"AI: {response.content}")
# >> AI: 你好 David！很高興認識你。你剛才告訴我你叫 David。

# 查看儲存的歷史
print(store["user_xyz"].messages)
```

> **[大師心法]**
> `RunnableWithMessageHistory` 完美體現了「關注點分離」的設計原則。你的核心 `chain` 專注於業務邏輯，而 `RunnableWithMessageHistory` 專注於歷史管理。這種模組化的設計讓你的程式碼更乾淨、更易於維護，並且可以輕鬆地在不同的記憶體後端（記憶體、SQL、Redis...）之間切換，只需修改 `get_session_history` 函數即可。
