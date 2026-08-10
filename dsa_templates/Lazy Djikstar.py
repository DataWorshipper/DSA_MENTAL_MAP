while pq:

    d, u = heapq.heappop(pq)

    if d != dist[u]:
        continue


    for v in all_possible_nodes:
        cost = calculate_distance(u, v)

        if dist[v] > d + cost:
            dist[v] = d + cost
            heapq.heappush(pq, (dist[v], v))

  
    for v, cost in special_edges[u]:
        if dist[v] > d + cost:
            dist[v] = d + cost
            heapq.heappush(pq, (dist[v], v))
