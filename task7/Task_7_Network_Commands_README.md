# Computer Networks Lab --- Task 7 Command Cheat Sheet

This README summarizes the important Cisco IOS commands covered in
**Task 7: Router Configuration and Network Address Translation (NAT)**.

> **Note:** Interface names depend on the router model in Packet Tracer.
> Check them with `show ip interface brief` and substitute the correct
> names if needed.

------------------------------------------------------------------------

## Task 7(a): Router Configuration

### 1. Enter configuration mode

``` text
Router> enable
Router# configure terminal
```

-   `enable` enters privileged EXEC mode.
-   `configure terminal` enters global configuration mode.

### 2. Configure a router interface

Example: configure `FastEthernet0/0` as `10.0.0.2/24`.

``` text
Router(config)# interface fastethernet0/0
Router(config-if)# ip address 10.0.0.2 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit
```

-   `interface fastethernet0/0` selects the interface.
-   `ip address ...` assigns the interface IP and subnet mask.
-   `no shutdown` enables the interface.
-   `exit` returns to the previous configuration mode.

### 3. Configure passwords

``` text
Router(config)# enable secret griet1234
Router(config)# line console 0
Router(config-line)# password 1234
Router(config-line)# login
Router(config-line)# exit
Router(config)# line vty 0 4
Router(config-line)# password g1234
Router(config-line)# login
Router(config-line)# exit
```

-   `enable secret` sets the password used to enter privileged EXEC
    mode.
-   `line console 0` configures local console access.
-   `line vty 0 4` configures the virtual terminal lines commonly used
    for remote CLI access.
-   `password` sets a line password; `login` makes IOS prompt for it.
-   Use lab-only passwords in practice; don't reuse these examples for
    real systems.

### 4. Verify and save

``` text
Router# show ip interface brief
Router# show running-config
Router# show startup-config
Router# copy running-config startup-config
```

-   `show ip interface brief` summarizes interface IPs and status.
-   `show running-config` shows the active configuration in RAM.
-   `show startup-config` shows the saved configuration used at startup.
-   `copy running-config startup-config` saves the current
    configuration.

**Interface status:** `up/up` means the interface and its line protocol
are operational. If an interface is administratively down, enter
interface configuration mode and use `no shutdown`.

### 5. Basic connectivity test

On a PC command prompt:

``` text
ping 10.0.0.2
```

Use the actual destination IP in your topology. For devices in the same
subnet, ensure their IP addresses and subnet masks are compatible. For
communication to other networks, configure a suitable default gateway
and routing.

------------------------------------------------------------------------

## Task 7(b): Network Address Translation (NAT)

NAT translates IP addresses as packets pass through a router.

### Key terms

-   **Inside local:** the private IP address of an internal device,
    e.g. `10.0.0.2`.
-   **Inside global:** the address representing that internal device to
    the outside network, e.g. `200.100.50.25`.
-   **Inside interface:** router interface facing the private LAN.
-   **Outside interface:** router interface facing the external network.

### 1. Mark inside and outside interfaces

Example: `FastEthernet0/0` faces the private LAN and `FastEthernet0/1`
faces the external network.

``` text
Router(config)# interface fastethernet0/0
Router(config-if)# ip nat inside
Router(config-if)# exit
Router(config)# interface fastethernet0/1
Router(config-if)# ip nat outside
Router(config-if)# exit
```

Configure IP addresses and enable both interfaces separately as required
by your topology.

### 2. Static NAT

Creates a permanent one-to-one mapping between a private IP and a
public-facing IP.

``` text
Router(config)# ip nat inside source static 10.0.0.2 200.100.50.25
```

Meaning:

``` text
Inside local (private): 10.0.0.2
Inside global (mapped): 200.100.50.25
```

The first IP is the internal device's address; the second is its
NAT-mapped address.

### 3. Dynamic NAT: select eligible private addresses

``` text
Router(config)# access-list 1 permit 10.0.0.0 0.0.0.255
```

-   `1` identifies the numbered ACL.
-   `permit` selects matching source addresses.
-   `10.0.0.0 0.0.0.255` matches addresses in `10.0.0.0/24`.

A wildcard mask is the inverse of the subnet mask: subtract each
subnet-mask octet from `255`. For example, `255.255.255.0` corresponds
to `0.0.0.255`.

### 4. Create a public address pool

``` text
Router(config)# ip nat pool PUBLIC_POOL 200.100.50.25 200.100.50.27 netmask 255.255.255.0
```

This defines the pool `PUBLIC_POOL` with addresses from `200.100.50.25`
through `200.100.50.27`.

### 5. Associate the ACL with the pool

``` text
Router(config)# ip nat inside source list 1 pool PUBLIC_POOL
```

This tells the router to use addresses from `PUBLIC_POOL` for traffic
whose inside source addresses match ACL `1`.

Dynamic NAT needs an available pool address for each simultaneous
translation. If the pool is exhausted, additional translations cannot be
created until an address becomes available.

### 6. PAT (NAT overload) --- useful extra command

PAT lets multiple inside devices share one outside interface address by
distinguishing sessions using port numbers.

``` text
Router(config)# access-list 1 permit 10.0.0.0 0.0.0.255
Router(config)# ip nat inside source list 1 interface fastethernet0/1 overload
```

Here `fastethernet0/1` must be the correctly configured outside
interface. PAT is different from Dynamic NAT using a pool: PAT can share
one interface address among multiple devices.

### 7. Verify NAT

``` text
Router# show ip nat translations
Router# show ip nat statistics
```

-   `show ip nat translations` displays active NAT mappings.
-   `show ip nat statistics` summarizes NAT activity and configuration.

For Dynamic NAT or PAT, generate traffic that matches the ACL before
expecting to see translations. Static NAT entries can appear as
permanent mappings.

------------------------------------------------------------------------

## Quick Comparison

  ------------------------------------------------------------------------------------------------------------------
  Type                    Mapping                 Typical command
  ----------------------- ----------------------- ------------------------------------------------------------------
  Static NAT              Permanent one-to-one    `ip nat inside source static 10.0.0.2 200.100.50.25`
                          mapping                 

  Dynamic NAT             Selects an address from `ip nat inside source list 1 pool PUBLIC_POOL`
                          a public pool           

  PAT / NAT overload      Many private devices    `ip nat inside source list 1 interface fastethernet0/1 overload`
                          share one public        
                          address using ports     
  ------------------------------------------------------------------------------------------------------------------

## Troubleshooting checklist

1.  Check interface names and states with `show ip interface brief`.
2.  Confirm interfaces have the intended IP addresses and are enabled
    with `no shutdown`.
3.  Confirm `ip nat inside` is on the private-facing interface and
    `ip nat outside` is on the external-facing interface.
4.  Check that the ACL matches the intended private addresses.
5.  For Dynamic NAT, confirm the pool has available addresses.
6.  Generate matching traffic, then inspect `show ip nat translations`.
7.  Make sure the surrounding topology, IP addressing, default gateways,
    and routes are configured correctly. NAT alone does not create a
    working end-to-end network.

------------------------------------------------------------------------

**Reminder:** Replace example IP addresses and interface names with
those used in your Packet Tracer topology.
