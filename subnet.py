import ipaddress

# Input the IP address and subnet prefix length
ip_address = input("Enter IP address (e.g., 192.168.1.0): ")
subnet_prefix_length = int(input("Enter subnet prefix length (e.g., 24 for /24): "))

# Calculate subnet mask
subnet_mask = ipaddress.IPv4Network(ip_address + '/' + str(subnet_prefix_length), strict=False).netmask

# Display subnet mask
print(f"Subnet Mask: {subnet_mask}")

# Calculate number of subnets and hosts per subnet
total_subnets = 2 ** (32 - subnet_prefix_length)
hosts_per_subnet = 2 ** (32 - subnet_prefix_length) - 2  # Subtract 2 for network and broadcast addresses

# Display subnetting information
print(f"Number of Subnets: {total_subnets}")
print(f"Number of Hosts per Subnet: {hosts_per_subnet}")
