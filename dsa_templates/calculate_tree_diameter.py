diameter = 0

        def findDiameter(u,p):

            best1 , best2 = 0 , 0
            nonlocal diameter

            for v in adj[u]:
                if v == p:
                    continue

                h = dfs(v,u)

                if h + 1 > best1:
                    best2 = best1
                    best1 = h + 1
                   
                elif h + 1 > best2:
                    best2 = h + 1

                
            diameter = max(diameter , best1 + best2)
