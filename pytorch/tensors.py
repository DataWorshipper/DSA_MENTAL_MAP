import torch
print(torch.__version__)

if torch.cuda.is_available():
    print("GPU is available")
else:
    print("GPU aint available")

x=torch.tensor([1,2,3])
print(x.shape)
print(x.ndim)

# empty will just create a tensor  with the dims
x=torch.empty(2,3)
print(type(x))

x=torch.zeros(2,3)
print(x)

x=torch.ones(2,3)
print(x)

#use seed for consistency
torch.manual_seed(42)
x=torch.randn(2,3)
print(x)

#its not that u have to only give lists any iterable shall work
x=torch.tensor(((1,2,3),(3,3,3)))
print(x)
#all numbers from start to end-1
x=torch.arange(1,10)
print(x)

x=torch.linspace(1,3,30)
print(x)

x=torch.eye(2)
print(x)

x=torch.full((3,3),5)
print(x)

#Creating tensors of same shape of another tensor
x=torch.empty((2,3))
y=torch.empty_like(x)
z=torch.ones_like(x)
t=torch.zeros_like(x)

#Datatype
x=torch.tensor([1,2,3],dtype=torch.float32)
print(x)
print(x.dtype)
x=x.to(torch.float64)
print(x.dtype)

#Reduction Operations
x=torch.randint(size=(2,3),low=0,high=10)
x=x.to(torch.float32)
print(x)
print(torch.sum(x))
print(torch.mean(x))
print(torch.median(x))
print(torch.sum(x,axis=0))

#Argmax and Argmin
#dim=0->aggregrate along  cols
#dim=1->aggregrate along rows
y=torch.argmax(x,dim=0)
print(y)

#Copying a tensor
a=torch.tensor([1,2,3])
b=a
b[1]=3 # change in b leads to change in a, b points to same mem location of a
print(a)
print(b)

#
a=torch.tensor([1,2,3])
b=torch.clone(a)
b[1]=3 
print(a)
print(b)

#Reshaping tensors
a=torch.eye(4)
b=a.reshape((2,2,2,2))
print(b)
#Permute
b=torch.randn((2,3,4))
print(b.permute((2,0,1)).shape)
#Unsqueeze->adds a dimension

c=torch.randn((226,226,3))
print(c.unsqueeze(0).shape)

#Squeeze
a=torch.randn((1,20))
print(a.squeeze(0).shape)





