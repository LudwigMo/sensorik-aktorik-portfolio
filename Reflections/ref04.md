**Limitations**

The HD-38 detects electrical conductivity between its metal probes rather than measuring the exact liquid level.

We initially encountered a loose power connection, which caused invalid readings. After restoring the 3.3 V supply and adjusting the potentiometer, the sensor successfully distinguished between dry and wet conditions.

We implemented a 300 ms software debounce to reduce unwanted switching caused by short signal fluctuations. However, debouncing is not equivalent to hysteresis. Debouncing requires a stable signal over time, whereas hysteresis uses different thresholds for switching between states.

Although we adjusted the detection threshold using the potentiometer, we did not implement or experimentally verify separate wet and dry thresholds. This remains a possible improvement for future experiments.

The switching behavior may also be affected by water conductivity, probe contamination, and corrosion. Therefore, the HD-38 is suitable for our laboratory demonstration but would require additional validation before use in a real marine environment.
