import sys

# Define the network graph as an adjacency matrix
network_graph = {
    'A': {'B': 2, 'C': 1},
    'B': {'A': 2, 'C': 3, 'D': 1},
    'C': {'A': 1, 'B': 3, 'D': 4},
    'D': {'B': 1, 'C': 4}
}

# Initialize distance vector with infinity for all nodes except 'A'
distance_vector = {node: sys.maxsize for node in network_graph}
distance_vector['A'] = 0

# Define a function to update the distance vector
def update_distance_vector():
    for node in network_graph:
        for neighbor, cost in network_graph[node].items():
            if distance_vector[node] + cost < distance_vector[neighbor]:
                distance_vector[neighbor] = distance_vector[node] + cost

# Perform iterations to update the distance vector until convergence
for _ in range(len(network_graph) - 1):
    update_distance_vector()

# Print the resulting distance vector
print("Distance Vector:")
for node, distance in distance_vector.items():
    print(f"{node}: {distance}")
