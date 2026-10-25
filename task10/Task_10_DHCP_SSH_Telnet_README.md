# Task 10 — DHCP, SSH and Telnet

Based on the Computer Networks lab manual, Task 10 (printed pages 71–75).

## Part A — DHCP server on a router

The manual demonstrates two networks:
- LAN1: `10.0.0.0/8`, gateway `10.0.0.1`
- LAN2: `20.0.0.0/8`, gateway `20.0.0.1`

### Configure DHCP pools

```text
enable
configure terminal
ip dhcp pool lan1
network 10.0.0.0 255.0.0.0
default-router 10.0.0.1
dns-server 8.8.8.8
exit
ip dhcp pool lan2
network 20.0.0.0 255.0.0.0
default-router 20.0.0.1
dns-server 8.8.8.8
exit
ip dhcp excluded-address 10.0.0.1
ip dhcp excluded-address 20.0.0.1
```

### Configure router interfaces

```text
interface fastethernet 0/0
ip address 10.0.0.1 255.0.0.0
no shutdown
exit
interface fastethernet 1/0
ip address 20.0.0.1 255.0.0.0
no shutdown
end
write memory
```

Use the actual interface names available on your router. The two LANs must be connected to the corresponding interfaces.

### Configure PCs and verify

For each PC: **Desktop → IP Configuration → DHCP**.

On the router:

```text
show ip dhcp binding
show ip dhcp pool
show ip interface brief
```

From a PC, test another host, for example:

```text
ping 20.0.0.3
```

## Part B — Telnet remote login to a switch

The manual's example uses switch management IP `10.0.0.2/8` on VLAN 1. Connect PC0's RS232 port to the switch Console port and configure via **Desktop → Terminal**.

```text
enable
configure terminal
interface vlan 1
ip address 10.0.0.2 255.0.0.0
no shutdown
exit
username myname password mypass
line vty 0 15
login local
transport input telnet
end
write memory
```

From a PC command prompt, after IP connectivity is configured:

```text
telnet 10.0.0.2
```

Log in with username `myname` and password `mypass`.

## Part C — SSH remote login to a switch

```text
enable
configure terminal
hostname myswitch
ip domain-name mydomain
username myname1 password mypass1
line vty 0 15
login local
transport input ssh
exit
crypto key generate rsa
```

When prompted for key size, enter a supported value (the manual uses `512`). Then:

```text
end
write memory
```

From a PC command prompt:

```text
ssh -l myname1 10.0.0.2
```

### Useful checks

```text
show running-config
show ip interface brief
show users
```

Note: SSH requires IP reachability, a hostname/domain name, a local username, and RSA keys. Use a different non-demo password for any real environment.
