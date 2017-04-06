# Machine Learning Notes

Entropy Based Metrics:

Entropy: min #bits to represent a random variable:
\begin{equation}
H[y] = -\mathbb{P}(y = 1) \log(\mathbb{P}(y = 1)) - \mathbb{P}(y = -1)\log(\mathbb{P}(y = -1))
\end{equation}

Cross Entropy: extra #bits if an imperfect distribution is used:
\begin{equation}
CE[\mathbb{P}|\hat{\mathbb{P}}] = -\mathbb{P}(y = 1) \log(\hat{\mathbb{P}}(y = 1)) - \mathbb{P}(y = -1)\log(\hat{\mathbb{P}}(y = -1))
\end{equation}

Relative Cross Entropy (RCE): CE relative to a baseline model:
\begin{equation}
RCE[\text{model}] = \frac{|CE[\text{model}] - CE[\text{baseline}]|}{|CE[\text{baseline}]|} \times 100\%
\end{equation}


