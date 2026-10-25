# Task 5 — Important Computer Networks Commands

Quick revision sheet for Task 5 (LAN, hub/switch, ping and ARP) in Packet Tracer.

## 1. PC commands (Desktop → Command Prompt)

| Command | Purpose |
|---|---|
| `ipconfig` | Displays the PC's IP address, subnet mask and gateway. |
| `ping 192.168.1.2` | Tests connectivity to another device. Replace the example IP with the target PC's IP. |
| `arp -a` | Displays the PC's ARP cache: known IP-to-MAC address mappings. |
| `arp -d` | Clears the ARP cache on systems that support it. Use only if you need to test ARP again. |

### Example
```text
ipconfig
ping 192.168.1.2
arp -a
```

The first ping may trigger ARP: the sender broadcasts an ARP request to discover the destination's MAC address, then stores the reply in its ARP cache.

## 2. Switch commands (Switch → CLI)

```text
enable
show mac address-table
show mac address-table dynamic
show interfaces status
show running-config
```

| Command | Purpose |
|---|---|
| `enable` | Enters privileged EXEC mode (`Switch#`). |
| `show mac address-table` | Displays MAC addresses learned by the switch and their ports. |
| `show mac address-table dynamic` | Shows dynamically learned MAC entries. |
| `show interfaces status` | Shows port status and basic port details. |
| `show running-config` | Displays the current active configuration. |

If `show mac address-table` is initially empty or incomplete, generate traffic first (for example, ping between PCs), then run the command again.

## 3. Key things to check in Packet Tracer

- Give each PC a unique IP address in the same subnet for a simple LAN.
- Use the same subnet mask on PCs in that subnet (for example, `255.255.255.0`).
- Connect PCs to the hub/switch with the appropriate Ethernet cables; Packet Tracer's automatic connection option can choose a suitable cable.
- Test with `ping <destination-IP>`.
- On a switch, use `show mac address-table` to see which MAC addresses were learned on which ports.
- A hub repeats incoming bits to its other ports; a switch learns MAC addresses and forwards frames based on its MAC address table.

## 4. Fast troubleshooting

1. Run `ipconfig` on both PCs and check their IP addresses and subnet masks.
2. Confirm the links are up (green indicators in Packet Tracer after convergence).
3. Ping the other PC using its IP address.
4. If the ping works, run `arp -a` on the PC and `show mac address-table` on the switch.
5. If it fails, check for duplicate IPs, incorrect subnet masks, disconnected links, or a wrong destination IP.

**Note:** `arp -a` is a PC command, not a Cisco switch command. `show mac address-table` is a Cisco switch command, not a PC command.
