# Generative AI Week 8: Evaluating LLMs

## Overview

- Topic of the unit: Measuring the **quality of generated text** and LLM performance using automatic metrics (BLEU, ROUGE) and model-centric metrics (Perplexity).
- Instructor: Mitra Purandare
- Learning goals:
  - Understand **BLEU** (n-gram precision + brevity penalty) and when it is appropriate
  - Understand **ROUGE** (recall-oriented overlap for summarization) and its variants (ROUGE-N, ROUGE-L, ROUGE-S)
  - Understand **Perplexity** as exponentiated average negative log-likelihood and how to interpret it
  - Recognize limitations: why automatic metrics may not match human judgments

## 1. Introduction / Context

Evaluating LLM outputs is hard because “good” text depends on **meaning, correctness, style, and usefulness**. This lecture focuses on common automatic evaluation approaches:

- **Overlap-based metrics** for tasks like translation and summarization (BLEU, ROUGE)
- **Language-model confidence metrics** based on probability of sequences (Perplexity)

The key theme: these metrics are useful, but each has failure modes—so you must choose them “fit for purpose.”

## 2. Key Concepts and Definitions

| Term                 | Definition                                                                                                                                         | Example                                                          |
| -------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------- |
| BLEU                 | Precision-oriented n-gram overlap metric used often in machine translation; typically combined across n=1..4 and penalized if output is too short. | Compare generated translation to reference using shared n-grams. |
| Brevity Penalty (BP) | Penalty applied in BLEU if candidate is shorter than reference to avoid overly short outputs scoring too well.                                     | Very short candidate → lower BLEU even if words match.           |
| ROUGE                | Recall-oriented overlap metric used often for summarization; measures how much of the reference summary is “covered.”                              | Summary should include key reference content.                    |
| ROUGE-N              | n-gram overlap (recall-focused).                                                                                                                   | ROUGE-1 = unigram overlap.                                       |
| ROUGE-L              | Longest Common Subsequence (LCS) between reference and prediction; captures some sentence-level structure.                                         | Preserves relative order even with gaps.                         |
| ROUGE-S              | Skip-bigram overlap; checks whether words appear in the same order even if not consecutive.                                                        | Measures ordered co-occurrence.                                  |
| Perplexity (PPL)     | Exponentiated average negative log-likelihood of a sequence under a language model; lower is better.                                               | Model “hesitates between fewer tokens” → lower PPL.              |
| Validation loss      | Loss computed on held-out data; perplexity is a transformed view of this for language modeling.                                                    | PPL = exp(loss) in the common setup.                             |

## 3. Main Content

### 3.1 BLEU: n-gram Overlap for Translation and Similar Tasks

BLEU evaluates a candidate sentence by comparing its **n-grams** to a **reference**. The slides illustrate that BLEU can distinguish:

- A correct sentence with the right order
- A scrambled sentence with the same words but wrong structure

**Example (from the slides):** reference “there is a laptop on the table”

- Model1: identical → shares all 2-grams
- Model2: “table the laptop is on a there” → shares far fewer 2-grams

**Key idea about n:**

- Low n (e.g., unigrams) captures more about shared content/meaning
- High n (e.g., 4-grams) captures fluency and well-formed phrasing

#### BLEU with brevity penalty

The lecture defines:

- Compute BLEU(\_n) for n=1..4
- Combine them via a geometric mean (“MEAN_BLEU”)
- Apply brevity penalty (BP)
  $$
  \text{BLEU} = \text{BP} \cdot \text{MEAN BLEU}
  $$
  This is meant to reduce the score of outputs that match some n-grams but are **too short**.

#### “BLEU at your own risk”

The slides explicitly warn BLEU can be misleading because it:

- Doesn’t truly evaluate meaning
- Doesn’t directly model sentence structure beyond n-grams
- Struggles with morphologically rich languages
- Often correlates poorly with human judgments

### 3.2 ROUGE: Summarization-Oriented Metrics

ROUGE is presented as a common choice for **summarization**, with an emphasis that **high recall** matters: a good summary should cover key points from the reference.

#### ROUGE variants

- **ROUGE-N:** n-gram overlap (BLEU-like but recall-focused)
- **ROUGE-L:** longest common subsequence (LCS), capturing order/structure better than pure n-grams
- **ROUGE-S:** skip-bigram overlap (words in same order, not necessarily adjacent)

#### Worked token examples (intuition)

The slides provide token lists to illustrate ROUGE calculation, e.g.:

- Reference: `["the","cat","sat","on","the","mat"]`
- Prediction: `["the","cat","is","on","the","mat"]`
  Here, ROUGE-1 would count overlapping unigrams (most match), while ROUGE-L would reflect that the sequence is largely aligned except for one word.

A second example shows that changing order (e.g., `["the","mat","sat","on","the","cat"]`) can reduce structure-sensitive scores even if many words are shared.

### 3.3 Perplexity: Probability-Based Evaluation of Language Models

Perplexity measures how “surprised” a model is by a sequence—i.e., how much probability it assigns to the correct next tokens.

The slides define perplexity as the exponentiated average negative log-likelihood over a tokenized sequence ($X=(x*1,\dots,x_T)$):

$$
\text{PPL}(X)=\exp\left(-\frac{1}{T}\sum*{t=1}^{T}\log p(x*t \mid x*{<t})\right)
$$

#### Interpretation (from the slides)

- Range intuition:
  - **Perfect prediction:** PPL = 1
  - **Worst case (uniform uncertainty):** tends toward vocabulary size (intuition: the model is “equally unsure among all tokens”)

- “Hesitation” view: if perplexity drops (e.g., 70 → 20), the model is effectively uncertain among fewer plausible tokens.
- Comparability caveat: PPL depends on the **tokenizer** and the **benchmark**; you should compare perplexity only under consistent setups.

#### Example sequence (from the slides)

“The golfer drove to the golf course.” is treated as an 8-token prediction chain:

$$
p(y_1 \mid x),; p(y_2 \mid y_1,x),; \dots,; p(y_8 \mid y_{1:7},x)
$$

If all these probabilities were 1 → PPL = 1. If each step is uniformly uncertain with probability (1/L), perplexity moves toward (L).

#### Fine-tuning and perplexity

The slides note an expectation: after fine-tuning on a task/domain dataset, the model should become more confident in next-token prediction for that distribution—so **perplexity should improve (decrease)**.

## 4. Relationships and Interpretation

These metrics evaluate different “layers” of quality:

- **BLEU / ROUGE**: compare output to references via surface overlap
  - Useful when reference-based evaluation makes sense (translation, summarization)
  - Can miss paraphrases or semantic equivalence

- **Perplexity**: measures model fit to a distribution (how well it predicts text)
  - Good for language modeling quality and training progress
  - Not a direct measure of factual correctness, task success, or helpfulness

**Rule of thumb:** overlap metrics approximate _similarity to a reference_, perplexity approximates _probabilistic confidence_, but neither guarantees “good answers” for open-ended assistant behavior.

## 5. Examples and Applications

- **Machine translation evaluation:** Use BLEU to compare candidate translations against references, especially when you have many test pairs.
- **Summarization evaluation:** Use ROUGE to measure content coverage versus reference summaries; prefer recall-oriented thinking for “did we include the key points?”
- **Training monitoring:** Track perplexity on validation data to see whether model changes (e.g., fine-tuning) improve next-token prediction on the target dataset.

## 6. Summary / Takeaways

- **BLEU** uses n-gram overlap (often 1–4 grams) and a **brevity penalty**, but can correlate poorly with human judgment and doesn’t truly measure meaning.
- **ROUGE** is widely used for summarization and is **recall-oriented**, with variants that capture n-gram overlap (ROUGE-N) and some structure/order (ROUGE-L, ROUGE-S).
- **Perplexity** measures how well a language model predicts a sequence; lower is better, but comparisons depend on tokenizer and benchmark.
- No single metric fully represents human-perceived quality—metric choice must match the task.

## 7. Study Tips

- Be able to explain (and compute on toy examples):
  - What an **n-gram** is and how overlap changes with word order
  - Why BLEU needs **brevity penalty**
  - Why ROUGE emphasizes **recall** for summaries

- For perplexity:
  - Practice deriving the formula from negative log-likelihood
  - Interpret “PPL ≈ number of tokens the model is unsure between” as an intuition (not a literal truth)

- When choosing a metric, always ask:
  - “Do I have good references?”
  - “Is paraphrasing acceptable?”
  - “Am I evaluating meaning, or surface similarity?”

## 8. Deepening / Further Concepts

- Combine automatic metrics with **human evaluation** when outputs are open-ended (assistant responses) and references are ambiguous.
- Consider task-specific evaluation schemes (e.g., factuality checks, retrieval-grounded scoring for RAG), because overlap alone can reward fluent but incorrect text.
- Use multiple metrics together (e.g., ROUGE-L + ROUGE-1 + human spot checks) to reduce blind spots.

## 9. Sources & Literature (IEEE)

[1] M. Purandare, “Evaluating LLMs,” lecture slides, Generative AI, OST – Ostschweizer Fachhochschule, 04.11.2025.

[2] K. Papineni, S. Roukos, T. Ward, and W.-J. Zhu, “BLEU: a Method for Automatic Evaluation of Machine Translation,” 2002.

[3] C.-Y. Lin, “ROUGE: A Package for Automatic Evaluation of Summaries,” 2004.
