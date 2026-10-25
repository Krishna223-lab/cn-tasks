# Task 9 — Dynamic Routing (RIP and OSPF)

Based on the Computer Networks lab manual, Task 9 (printed pages 66–70).

## Topology and addressing

| Device | Interface | IP address | Mask |
|---|---|---|---|
| Router0 / R1 | Fa0/0 | `10.0.0.1` | `255.0.0.0` |
| Router0 / R1 | Se2/0 | `20.0.0.1` | `255.0.0.0` |
| Router1 / R2 | Se3/0 | `20.0.0.2` | `255.0.0.0` |
| Router1 / R2 | Fa0/0 | `192.168.1.1` | `255.0.0.0` (manual) |
| PC0 | NIC | `10.0.0.2` | `255.0.0.0` |
| PC1 | NIC | `10.0.0.3` | `255.0.0.0` |
| PC2 | NIC | `192.168.1.2` | `255.0.0.0` (match router/manual) |
| PC3 | NIC | `192.168.1.3` | `255.0.0.0` (match router/manual) |

Gateways: PC0/PC1 → `10.0.0.1`; PC2/PC3 → `192.168.1.1`.

> Interface names depend on the router model. Use `show ip interface brief` to confirm. The manual's OSPF section uses the wildcard mask `0.0.0.255` in its network statements even though the interface masks shown are `/8`; the commands below preserve the manual's statements.

## Router interface setup

### Router0 / R1

```text
enable
configure terminal
interface fastethernet 0/0
ip address 10.0.0.1 255.0.0.0
no shutdown
exit
interface serial 2/0
ip address 20.0.0.1 255.0.0.0
no shutdown
exit
end
write memory
```

### Router1 / R2

```text
enable
configure terminal
interface fastethernet 0/0
ip address 192.168.1.1 255.0.0.0
no shutdown
exit
interface serial 3/0
ip address 20.0.0.2 255.0.0.0
no shutdown
exit
end
write memory
```

If the serial link is down, check cabling and interface names. Configure `clock rate 64000` only on the serial DCE side if required.

## Option A — RIP version 2

On Router0 / R1:

```text
enable
configure terminal
router rip
version 2
network 10.0.0.0
network 20.0.0.0
no auto-summary
end
write memory
```

On Router1 / R2:

```text
enable
configure terminal
router rip
version 2
network 20.0.0.0
network 192.168.1.0
no auto-summary
end
write memory
```

## Option B — OSPF

If you want to test OSPF alone, remove RIP on both routers first:

```text
enable
configure terminal
no router rip
end
```

On Router0 / R1:

```text
enable
configure terminal
router ospf 1
network 10.0.0.0 0.0.0.255 area 0
network 20.0.0.0 0.0.0.255 area 0
end
write memory
```

On Router1 / R2:

```text
enable
configure terminal
router ospf 1
network 192.168.1.0 0.0.0.255 area 1
network 20.0.0.0 0.0.0.255 area 0
end
write memory
```

## Verification commands

```text
show ip interface brief
show ip protocols
show ip route
show ip ospf neighbor
show running-config
ping 20.0.0.2
```

From PC0:

```text
ping 192.168.1.3
```

Route codes: `R` = learned by RIP; `O` = learned by OSPF. The serial interfaces need valid IPs and must be operational for routing between the LANs.
