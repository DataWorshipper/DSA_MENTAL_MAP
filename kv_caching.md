# KV Caching

## References

- [KV Caching Explained (Hugging Face)](https://huggingface.co/blog/not-lain/kv-caching)
 
## Intuition

Suppose the prompt is

```
My name is Abhiraj
```

During the **first forward pass (Prefill)**, the model computes the **Q, K and V vectors** for **every token**.

```
My        ---> Q1 K1 V1
name      ---> Q2 K2 V2
is        ---> Q3 K3 V3
Abhiraj   ---> Q4 K4 V4
```

This has to be done because the model has never seen these tokens before.

---

## After the First Token is Generated

Suppose the model generates

```
works
```

Now autoregressive generation starts.

The important observation is:

- `WQ`, `WK` and `WV` are fixed during inference.
- Therefore, for all the previous tokens, their **Key** and **Value** vectors will never change.

So there is no point computing

```
K1 V1
K2 V2
K3 V3
K4 V4
```

again.

Instead, we simply **cache** them.

```
KV Cache

K1 V1
K2 V2
K3 V3
K4 V4
```

---

## Generating the Next Token

Now we only have one new token:

```
works
```

We pass only this token through

```
WQ
WK
WV
```

to obtain

```
Q5 K5 V5
```

Now we already have

```
K1 K2 K3 K4
V1 V2 V3 V4
```

stored.

So attention becomes

```
          Cached Keys
               │
               ▼

Q5 × [K1 K2 K3 K4 K5]
```

This computes **only the last row** of the attention matrix.

The attention scores are then multiplied with

```
[V1 V2 V3 V4 V5]
```

to obtain the attention output for the new token.

After this,

```
K5
V5
```

are also stored inside the KV Cache.

---

## Growing KV Cache

```
Step 1

Prompt

My
name
is
Abhiraj

KV Cache

K1 V1
K2 V2
K3 V3
K4 V4


----------------------------


Step 2

Generated

works

Compute only

Q5 K5 V5

Append

KV Cache

K1 V1
K2 V2
K3 V3
K4 V4
K5 V5


----------------------------


Step 3

Generated

at

Compute only

Q6 K6 V6

Append

KV Cache

K1 V1
K2 V2
K3 V3
K4 V4
K5 V5
K6 V6
```

---

## Attention Matrix

Without KV Cache, every decoding step would recompute the entire matrix.

```
        K1 K2 K3 K4 K5
      +----------------
Q1    |
Q2    |
Q3    |
Q4    |
Q5    |
```

With KV Cache, all the previous Keys and Values are already available.

Only the newest Query is computed.

```
        K1 K2 K3 K4 K5
      +----------------
Q1    |  Already done
Q2    |  Already done
Q3    |  Already done
Q4    |  Already done
Q5    |  Compute only this row
```

---

## Complexity

Without KV Cache

- Recompute Q, K and V for every previous token.
- Decoding complexity is roughly **O(n²)**.

With KV Cache

- Compute Q, K and V only for the newest token.
- Reuse all previous Keys and Values.
- Only the last row of attention is computed.
- Decoding complexity becomes roughly **O(n)**.

---

## One Line Summary

> During prefill, compute Q, K and V for every token. During autoregressive decoding, only compute Q, K and V for the newest token, reuse all previously computed Keys and Values from the KV Cache, and compute only the last row of the attention matrix.
