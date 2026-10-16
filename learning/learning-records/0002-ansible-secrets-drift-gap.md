# Ansible proposal missed the idempotency/drift interaction with Terraform

In session-08, the user proposed a default-password-plus-fast-Ansible-rotation
scheme for secrets, and only derived (correctly, once nudged) that the next
`terraform apply` would reset the rotated password — i.e. two systems
writing to the same piece of state without coordination. This suggests the
user doesn't yet have idempotency as an instinctive lens for spotting this
class of bug ahead of time; they can derive the specific consequence when
asked, but didn't predict it. Teaching should center idempotency as the
core Ansible concept, specifically in contrast to Terraform's own state
model, rather than treating idempotency as a side fact.
