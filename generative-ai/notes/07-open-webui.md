# Genterative AI Week 7: Open WebUI Setup, RAG, MCP Integration, and Useful Services

## Overview

- Topic of the unit: Practical tooling around **Open WebUI**—installation (Docker/Docker Compose), persistence, connecting to **LLMHub** endpoints, enabling **RAG**, integrating **MCP servers**, and extending Open WebUI via **pipelines**.
- Instructor: Mitra Purandare
- Learning goals:
  - Install and run **Open WebUI** using Docker/Docker Compose with persistent storage
  - Configure Open WebUI to connect to a hosted LLM endpoint (LLMHub)
  - Understand where to enable and configure **RAG** in Open WebUI
  - Connect **MCP** tools/servers to Open WebUI
  - Extend Open WebUI with **pipelines**

## 1. Introduction / Context

This week is a hands-on “operations and integration” unit: rather than focusing on model internals, it focuses on the **infrastructure and ecosystem** needed to run and extend an LLM interface in practice.

Open WebUI is treated as the central hub:

- you run it locally (ideally in Docker),
- connect it to an LLM API endpoint (LLMHub),
- optionally add **RAG** for document-based answers,
- and attach tools via **MCP** for agent-like workflows.

## 2. Key Concepts and Definitions

| Term                             | Definition                                                                               | Example                                                    |
| -------------------------------- | ---------------------------------------------------------------------------------------- | ---------------------------------------------------------- |
| Open WebUI                       | A web-based UI for interacting with LLM backends, with features like RAG and extensions. | Running a local chat UI that calls a remote LLM endpoint.  |
| Docker / Docker Compose          | Container tooling to run Open WebUI reliably with minimal local setup.                   | Start Open WebUI as a container with a compose file.       |
| Persistent volume mapping (`-v`) | Docker mechanism to persist data/config between container restarts.                      | Mapping a local folder to keep settings after updates.     |
| LLMHub                           | Hosted service providing LLM access via an API endpoint.                                 | Configure Open WebUI to use an OpenAI-compatible base URL. |
| Connection string                | The base URL Open WebUI uses to talk to an API backend.                                  | `https://api.llmhub.infs.ai/v1`                            |
| RAG                              | Retrieval-Augmented Generation in Open WebUI to answer with document context.            | Upload docs → retrieve chunks → answer grounded in docs.   |
| Docling / MinerU                 | Document-processing services mentioned for RAG ingestion pipelines.                      | Use Docling (CPU, slow) or MinerU for document processing. |
| MCP                              | Model Context Protocol to expose tools/servers to an LLM app.                            | Connect an MCP server so the UI can call tools.            |
| Pipelines                        | Extension mechanism in Open WebUI to add/modify workflows.                               | Custom pipeline to preprocess prompts or route models.     |

## 3. Main Content

### 3.1 Getting Started with Open WebUI (Recommended: Docker)

The slide recommends using **Docker or Docker Compose** to start Open WebUI, and explicitly notes the importance of mapping a **persistent volume** so changes survive restarts/updates.

Key operational principle:

- **Without a volume map**: settings/uploads may be lost when the container is recreated.
- **With a volume map (`-v`)**: configuration and data remain persistent.

Useful references (as provided):

```text
Open WebUI docs: https://docs.openwebui.com
Quick start (Docker): https://docs.openwebui.com/getting-started/quick-start/
```

### 3.2 Connecting Open WebUI to a Hosted LLM Backend (LLMHub)

The slides list IFS services for using hosted LLMs:

- LLMHub website and API
- A concrete Open WebUI “connection string” / base URL

Provided endpoints:

```text
LLMHub: https://llmhub.infs.ai
API: https://api.llmhub.infs.ai
Open WebUI connection string: https://api.llmhub.infs.ai/v1
```

Interpretation:

- Open WebUI acts as the **client UI**
- LLMHub provides the **model serving endpoint**
- The connection string is the configuration “bridge” between them.

### 3.3 Enabling RAG in Open WebUI

RAG is highlighted as a built-in Open WebUI feature, with a documentation link included.

Provided reference:

```text
Open WebUI RAG feature docs: https://docs.openwebui.com/features/rag/
```

The same slide points to two document-processing backends/services:

**Docling (slow, CPU-only)**

```text
Frontend: https://docling.infs.ai/ui/
API: http://docling.infs.ai
```

**MinerU**

```text
Frontend: https://mineru.infs.ai
API: https://api.mineru.infs.ai
```

Practical implication:

- RAG quality depends heavily on document ingestion (splitting, parsing, extracting clean text).
- Different processors can trade speed vs extraction quality.

### 3.4 MCP: Connecting Tools to Open WebUI

Week 7 connects conceptually to “agents” by adding **tools** via MCP:

- an MCP SDK tutorial link,
- and the Open WebUI documentation page for connecting MCP servers.

Provided references:

```text
MCP Python SDK tutorial: https://github.com/modelcontextprotocol/python-sdk?tab=readme-ov-file#quickstart
Connect MCP to Open WebUI: https://docs.openwebui.com/openapi-servers/mcp/
```

High-level flow:

- MCP servers expose tools
- Open WebUI connects to those servers
- The UI can then offer tool capabilities in the chat workflow.

### 3.5 Extending Open WebUI with Pipelines

The slide also points to “pipelines” as a way to extend Open WebUI.

Provided reference:

```text
Pipelines docs: https://docs.openwebui.com/features/pipelines/
```

Interpretation:

- Pipelines are a customization layer to adapt behavior without rewriting the whole app
- Examples could include prompt preprocessing, routing requests, or postprocessing outputs (conceptually).

## 4. Relationships and Interpretation

This week is essentially a deployment + integration map:

- **Docker** gives reproducible deployment
- **Volume mapping** makes it production-usable (persistence)
- **LLMHub connection string** plugs the UI into a model backend
- **RAG** adds private/document knowledge
- **MCP** adds tool calling (agent capability)
- **Pipelines** add customization hooks to tailor the system end-to-end

## 5. Examples and Applications

- **Local LLM UI + hosted inference**: run Open WebUI locally, connect it to `https://api.llmhub.infs.ai/v1`, and use it as your daily chat interface.
- **Document Q&A**: enable RAG and connect a document-processing backend (Docling or MinerU) to turn PDFs into searchable knowledge for grounded answers.
- **Tool-augmented assistant**: connect an MCP server that exposes utilities (DB queries, Git operations, ticket creation) so Open WebUI can act beyond chat.
- **Custom workflows**: implement a pipeline that enforces response format, adds system policies, or routes queries to different models depending on topic.

## 6. Summary / Takeaways

- Use **Docker/Docker Compose** for Open WebUI, and always map a **persistent volume** for durability.
- Open WebUI can connect to hosted model endpoints (LLMHub) via a base URL like `https://api.llmhub.infs.ai/v1`.
- **RAG** is a first-class feature; ingestion backends like **Docling** and **MinerU** can support document processing.
- **MCP integration** connects tools to the UI, enabling agent-like capabilities.
- **Pipelines** are the extension mechanism for customized workflows in Open WebUI.

## 7. Study Tips

- Be able to explain why persistence matters: what breaks if you forget `-v` volume mapping.
- Practice the “three-layer architecture” story:
  1. UI (Open WebUI)
  2. Model endpoint (LLMHub)
  3. Knowledge/tools layer (RAG + MCP)

- For RAG troubleshooting, focus on ingestion quality: bad parsing → bad retrieval → bad answers.
- For MCP, remember: Open WebUI is the host/client side; MCP servers provide tool capabilities.

## 8. Deepening / Further Concepts

- Combine **RAG + MCP**: retrieve the right context _and_ call the right tools (e.g., retrieve policy + create ticket).
- Use pipelines as a governance layer: enforce templates, include citations, apply safety rules, or route by domain.
- Consider hybrid retrieval (keyword + embeddings) if document parsing or domain vocabulary causes misses (conceptual link to prior RAG lectures).

## 9. Sources & Literature (IEEE)

[1] M. Purandare, “Open WebUI – Useful Links,” Week 7 course handout/slide, Generative AI, OST – Ostschweizer Fachhochschule.
