N = int(input())
tree = [[] for _ in range(N + 1)]
for _ in range(N -1):
    u , v = map(int,input().split())
    tree[u].append(v)
    tree[v].append(u)
    
    
diameter = 0  

def dfs(node,parent):
    
    global diameter
    best1 , best2 = 0 , 0
    
    
    for nei in tree[node]:
        if nei == parent:
            continue
        
        h = 1 + dfs(nei,node)
        
        if h > best1:
            best2 = best1
            best1 = h
        elif h > best2:
            best2 = h
            
            
    diameter = max(diameter,best1 + best2)  
    return best1
    
    
dfs(1,0)
print(diameter)
    
   
        
        

    
        
        
        
