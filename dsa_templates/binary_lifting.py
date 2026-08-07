n , q = map(int,input().split())
e = list(map(int , input().split()))

tree = [[] for _ in range(n + 1)]

for i in range(n - 1):
    u = e[i]
    v = i + 2
    tree[u].append(v)
    tree[v].append(u)

LOG = 20

up = [[-1] * (LOG + 1) for _ in range(n + 1)]
depth = [0] * (n + 1)

def dfs(u,p,d):
    
    up[u][0] = p
    depth[u] = d

    for v in tree[u]:
        if v == p:
            continue
        
        
        dfs(v,u,1 + d)
        
    


dfs(1,-1,0)

for k in range(1,1 + LOG):
    for u in range(1,n + 1):
        if up[u][k - 1] == -1:
            up[u][k] = -1
        else:
            up[u][k] = up[up[u][k - 1]][k - 1]
        
        
def query(u,k):
    
    i = 0
    
    while k and u != -1:
        
        
        if k & 1:
            u = up[u][i]
            
        i += 1
        k >>= 1
        
        
    
    return u
    
    
def lca(a , b):
    
    
    
    if depth[a] > depth[b]:
        a , b = b , a
        
        
    
    b = query(b,depth[b] - depth[a])
    
    if a == b:
        return a
        
    
        
    for k in range(LOG , - 1 , -1):
        if up[a][k] != up[b][k]:
            a = up[a][k]
            b = up[b][k]
    
    return up[a][0]
    
    


for _ in range(q):
    u , v = map(int,input().split())
    
    print(lca(u,v))


