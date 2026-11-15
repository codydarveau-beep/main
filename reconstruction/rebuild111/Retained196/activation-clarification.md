# User / previous-agent activation clarification

All twelve chapters' dialogue records were intentionally present, while released 1.10.0 exposed only chapters 1–4: twelve scenes. Dialogue-pack contents and runtime activation were separate.

- 1.10.0: release the four-chapter checkpoint.
- 1.11.0: finish integrating and validating the remaining chapters, companions and related systems, then enable the complete campaign.

Unpublished work added later-chapter staging, encounters, map aliases, travel connections and supporting systems. It did not establish completed, verified activation of all 36 scenes.

The last recorded private source still had:

```ini
CAMPAIGN_RELEASE_SCENES193 = 12
CAMPAIGN_OPENING_READY200 = 0
```

The second value was a private development readiness guard, not evidence that the released opening was disabled.

Preserve the later records. The twelve-scene ceiling was an intentional checkpoint restriction, not the final campaign design. Removing it belongs after verifying later runtime objectives, encounters, travel, recruitment and completion transitions; dialogue availability alone is insufficient.
