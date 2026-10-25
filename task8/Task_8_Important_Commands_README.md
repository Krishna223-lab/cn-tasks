# Task 8 — Important Cisco Packet Tracer Commands

This README covers **Task 8(a): VLANs and inter-VLAN routing** and **Task 8(b): static routing**.

> Use the interface names and IP addresses that match your Packet Tracer topology. Some router/switch models use different interface names.

---

## Task 8(a) — VLAN Configuration

### 1. Create VLANs

```text
enable
configure terminal
vlan 10
name VLAN10
exit
vlan 20
name VLAN20
exit
vlan 30
name VLAN30
exit
end
```

### 2. Assign an access port to a VLAN

Example: assign `FastEthernet0/1` to VLAN 10.

```text
configure terminal
interface fastEthernet 0/1
switchport mode access
switchport access vlan 10
end
```

Repeat for other ports, changing the interface and VLAN number as needed.

### 3. Configure a trunk link

Run on a switch port connected to another switch or to a multilayer switch:

```text
configure terminal
interface gigabitEthernet 0/1
switchport mode trunk
switchport trunk allowed vlan 10,20,30
end
```

Use the actual interface connected to the other switch. Some switch models do not require a trunk encapsulation command.

### 4. Configure inter-VLAN routing on a multilayer switch

Example addressing:
- VLAN 10 gateway: `10.0.0.254/24`
- VLAN 20 gateway: `10.0.20.254/24`

```text
enable
configure terminal
ip routing
interface vlan 10
ip address 10.0.0.254 255.255.255.0
no shutdown
exit
interface vlan 20
ip address 10.0.20.254 255.255.255.0
no shutdown
end
```

If using VLAN 30, create its SVI with an IP address in a **different subnet**. Configure each PC's default gateway as the SVI IP address for its VLAN.

### 5. Useful VLAN verification commands

```text
show vlan brief
show interfaces trunk
show ip interface brief
show ip route
show running-config
```

- `show vlan brief`: VLANs and access-port assignments.
- `show interfaces trunk`: trunk ports and allowed VLANs.
- `show ip interface brief`: interface addresses and status.
- `show ip route`: routing table on a Layer 3 device.

### 6. Save configuration

```text
copy running-config startup-config
```

---

## Task 8(b) — Static Routing

### 1. Example topology and addressing

| Device/interface | IP address | Subnet mask |
|---|---|---|
| Router0 FastEthernet0/0 | `10.0.0.3` | `255.0.0.0` |
| Router0 Serial2/0 | `20.0.0.1` | `255.0.0.0` |
| Router1 FastEthernet0/0 | `30.0.0.2` | `255.0.0.0` |
| Router1 Serial3/0 | `20.0.0.2` | `255.0.0.0` |
| PC0 | `10.0.0.1` | `255.0.0.0` |
| PC1 | `10.0.0.2` | `255.0.0.0` |
| PC2 | `30.0.0.1` | `255.0.0.0` |
| PC3 | `30.0.0.3` | `255.0.0.0` |

PC default gateways:
- PC0 and PC1: `10.0.0.3`
- PC2 and PC3: `30.0.0.2`

These are the example addresses used in this lab walkthrough. If your manual or topology specifies different values, use those values consistently.

### 2. Configure Router0

```text
enable
configure terminal
interface fastEthernet 0/0
ip address 10.0.0.3 255.0.0.0
no shutdown
exit
interface serial 2/0
ip address 20.0.0.1 255.0.0.0
no shutdown
exit
ip route 30.0.0.0 255.0.0.0 20.0.0.2
end
```

### 3. Configure Router1

```text
enable
configure terminal
interface fastEthernet 0/0
ip address 30.0.0.2 255.0.0.0
no shutdown
exit
interface serial 3/0
ip address 20.0.0.2 255.0.0.0
no shutdown
exit
ip route 10.0.0.0 255.0.0.0 20.0.0.1
end
```

**Important:** Interface names can differ by router model. If serial interfaces are not present, check the model/modules and use the actual interface names. On a serial link, if the DCE end requires it, configure `clock rate 64000` under that serial interface.

### 4. Static route syntax

```text
ip route <destination-network> <subnet-mask> <next-hop-IP>
```

Example:

```text
ip route 30.0.0.0 255.0.0.0 20.0.0.2
```

This tells Router0 how to reach the `30.0.0.0/8` network through Router1's serial IP.

### 5. Verification and troubleshooting commands

```text
show ip interface brief
show ip route
show running-config
ping 20.0.0.2
ping 30.0.0.2
```

Test connectivity in stages:
1. A PC pings its own default gateway.
2. Router0 pings Router1's serial IP.
3. Router0 pings Router1's LAN interface.
4. PC0 pings a PC on the remote LAN, such as `30.0.0.3`.
5. If remote PC pings fail, check both PCs' IP/mask/gateway and both routers' routes.

### 6. Save configuration

```text
copy running-config startup-config
```

---

## Quick command reference

| Goal | Command |
|---|---|
| Enter privileged mode | `enable` |
| Enter configuration mode | `configure terminal` |
| Configure an interface | `interface <interface-name>` |
| Enable an interface | `no shutdown` |
| Create a VLAN | `vlan <vlan-id>` |
| Assign an access VLAN | `switchport access vlan <vlan-id>` |
| Set a trunk | `switchport mode trunk` |
| Enable Layer 3 routing | `ip routing` |
| Add a static route | `ip route <network> <mask> <next-hop>` |
| View interface status | `show ip interface brief` |
| View routing table | `show ip route` |
| View VLANs | `show vlan brief` |
| View trunks | `show interfaces trunk` |
| View current configuration | `show running-config` |
| Save configuration | `copy running-config startup-config` |
