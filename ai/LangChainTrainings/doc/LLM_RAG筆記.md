🔹 RAG 是什麼？
RAG（檢索增強生成）是一種技術，讓大型語言模型（LLM）結合外部資料來產生更準確的回答。

常用於問答系統、聊天機器人等應用場景。

🔹 為什麼需要 RAG？
LLM 回答問題的能力取決於訓練時的資料。

如果問題涉及公司內部文件或最新資訊，模型可能無法準確回答。

使用 RAG，可以讓模型從外部來源（如 PDF、文件）取得上下文，即時查找資訊，不需微調模型。

🔹 RAG 的兩大流程
1. 提取與索引（Extract & Index）
將外部文件（如 PDF）轉為文字。
將長文本**切割成小區塊（chunk）**以適應模型的上下文限制。
例如 Llama 模型支援約 128K token 的上下文。
將這些文字區塊進行嵌入（Embedding）：轉為向量表示。

儲存到向量資料庫（Vector DB），如：

Chroma（推薦使用）
FAISS、Pinecone、Weaviate、Milvus 等
也支援 SQL、Elasticsearch、Cosmos DB 等資料庫

2. 檢索與生成（Retrieve & Generate）
接收使用者的提問。
根據提問從向量資料庫中找出最相似的區塊（context retrieval）。
將這些區塊與提問一起輸入 LLM。
由模型根據 context 回答問題。

🔹 嵌入模型（Embedding Model）來源
嵌入模型將文字轉為向量表示，用於相似度搜尋。
可使用的提供者：
OpenAI
Hugging Face
Cohere
Llama 3.1 / 3.2
Azure、Google、AWS、Mistral、IBM Watson 等

🔹 向量資料庫（Vector Store）選擇
Chroma 為開源、易用、支援增量更新與非同步操作。
其他選項如 FAISS、Pinecone、Qdrant、Weaviate、ElasticSearch。
可依場景選擇本地或雲端版本。

🔜 下一步
將從 PDF 開始進行「提取與索引」，也就是第一步：
讀取 PDF。
切割文本。
進行嵌入。
儲存到向量資料庫。

