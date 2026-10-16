# Argo CD's scope was initially overextended to cover infra deployment

During the system design mock interview (session-08), the user initially
proposed using Argo CD "to deploy infrastructure," and only corrected this
to "K8s workloads only, not infra" after a nudging question. This means the
starting point for Argo CD teaching is not zero — the user already has a
rough sense that Argo CD exists and deploys *something* — but the
infra/workload boundary needs to be taught explicitly and reinforced, since
it was the exact point of confusion. Future lessons should lead with that
boundary rather than assuming it's obvious once GitOps is explained.
