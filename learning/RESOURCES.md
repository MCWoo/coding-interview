# Multi-cloud Platform Engineering Resources

## Knowledge

- [Argo CD: Core Concepts](https://argo-cd.readthedocs.io/en/stable/core_concepts/)
  Official docs. Defines Application, sync, prune, self-heal, and the
  declarative-GitOps model directly. Use for: anything about what Argo CD
  actually reconciles and what it refuses to do.
- [Argo CD: Automated Sync Policy](https://argo-cd.readthedocs.io/en/stable/user-guide/auto_sync/)
  Official docs on `prune`/`selfHeal` flags and why pruning defaults off.
  Use for: the mechanics behind "Argo CD reverts manual kubectl changes."
- [Ansible: Introduction to Playbooks](https://docs.ansible.com/ansible/latest/playbook_guide/playbooks_intro.html)
  Official docs on playbook structure and idempotency. Use for: why a
  well-written task should converge to the same state on repeated runs.
- [Ansible: Protecting Sensitive Data with Ansible Vault](https://docs.ansible.com/ansible/latest/vault_guide/vault.html)
  Official docs. Use for: the Ansible-native answer to "don't commit a
  plaintext secret," and how it compares to Terraform state exposure.
- [OpenTelemetry: Concepts — Signals](https://opentelemetry.io/docs/concepts/signals/)
  Official docs on traces/metrics/logs as the three observability signal
  types. Use for: a vendor-neutral baseline before comparing AWS/Azure
  native tools.
- [Prometheus: Overview](https://prometheus.io/docs/introduction/overview/)
  Official docs on the metrics model this ecosystem is built around (and
  what Argo CD/K8s tooling commonly exports). Use for: what "the K8s-native
  metrics store" actually means in a design answer.

## Gaps

- No single official source compares Ansible and Terraform directly (their
  docs don't cross-reference each other, by design — they're separate
  projects). The comparison in `reference/ansible-cheatsheet.html` is
  synthesized from both tools' own docs plus general practitioner
  consensus; treat it as reasonable but not citable the way a single
  official doc is.
- No official source directly addresses "cross-cloud visibility" as a named
  problem — AWS and Azure each document their own native tools
  (CloudWatch, Azure Monitor) but neither publishes guidance on federating
  across both. The reference doc's take on this is a synthesis, flagged as
  such.

## Wisdom (Communities)

- Not yet explored — revisit once the knowledge base here is solid enough
  to make community discussion (e.g. r/devops, r/kubernetes, the
  CNCF/Argo Slack) productive rather than overwhelming.
