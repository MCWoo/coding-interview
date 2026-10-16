# Mission: Multi-cloud platform engineering (Argo CD, Ansible, observability)

## Why
A system design mock interview (`session-08`, targeted at the Viasat Senior
Cloud Platform Engineer posting) surfaced three concrete gaps: Argo CD's
actual scope was misunderstood until corrected mid-interview, the Ansible
proposal broke on an idempotency/drift issue that wasn't anticipated, and
cross-cloud observability/visibility wasn't addressed at all because the
underlying concepts weren't known. The goal is to close these gaps well
enough to design and defend a multi-cloud GitOps platform in a future mock
interview (or the real one) without needing a nudge to catch the same
mistakes.

## Success looks like
- Can state what Argo CD does and does not own (K8s manifest reconciliation
  vs. everything upstream of the cluster) without being prompted, and can
  explain self-heal/prune/sync in a design discussion.
- Can explain why a secret touched by both Ansible and Terraform drifts, and
  propose a design that doesn't have two systems fighting over the same
  value.
- Can sketch a cross-cloud observability approach (what the three pillars
  are, why AWS/Azure-native tools alone don't solve "what's running across
  both") well enough to answer a follow-up question on it in an interview.

## Constraints
- Learning happens between/around mock interview sessions in this repo —
  short, focused sessions, not a multi-week course commitment.
- Prior background: strong general software engineering and DS&A; this is
  new infrastructure/platform-engineering territory, not a from-scratch
  programming education.

## Out of scope
- Deep Kubernetes fundamentals beyond what's needed to reason about what
  Argo CD deploys (not re-deriving core K8s object model from scratch).
- Terraform itself — already reasonably familiar from the interview
  session; only the Terraform-Ansible secrets interaction is in scope.
- Hands-on cluster setup / running real infrastructure — this is interview
  readiness, not a home-lab project (revisit if that changes).
