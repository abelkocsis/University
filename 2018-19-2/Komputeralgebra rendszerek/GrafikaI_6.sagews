︠7bbab222-f874-42f3-806a-8d2961981c46︠

︡5206777a-5e65-426a-ac02-9f7edb28e045︡
︠55e6e863-dde6-48a7-8d9a-172ceedcde2a︠

︡50b65b8e-7476-4442-a0d8-e73ef5da49d2︡{"done":true}
︠566310db-36fd-467a-ab78-066ed8079a41︠

︡9b94a32a-87d2-4381-8a9d-4aaa30147e62︡{"done":true}
︠f0402377-3465-41de-9c85-9f1ef9838fda︠

︡31a67834-c95e-45d3-a8e7-ad25a4a1a85e︡{"done":true}
︠87461e26-1186-40aa-85f4-9cc8f9f4122es︠
#Forgatási mátrix
R = lambda phi : Matrix([[cos(phi), -sin(phi)], [sin(phi), cos(phi)]])

︡dd7196e8-fd64-4576-8695-0835d86e6056︡{"done":true}
︠e61d3606-39ca-4acd-80a4-49d3f81d2ab5o︠

︡84dacdf4-a54e-44c2-a6d8-f7b9f931d072︡
︠edfc81c8-c51e-44c1-b72e-26b972ea4ebcs︠
#Derékszögő háromszög adott oldalhosszokkal x0 kezdőponttal és phi elforgatási szöggel
triangle = lambda x0, phi : plot(line([x0, vector([0,3])*R(phi)+x0], color='purple') + text("a", (x0+vector([0,3])*R(phi)+x0)/2, color='purple') + line([x0, vector([4,0])*R(phi)+x0], color='blue' ) + text ("b", (x0 + vector([4,0])*R(phi)+x0)/2, color='blue') + line([vector([0,3])*R(phi)+x0, vector([4,0])*R(phi)+x0], color='orange') + text("c", (vector([0,3])*R(phi)+x0 + vector([4,0])*R(phi)+x0)/2, color='orange'))
︡d477f99a-67cf-4009-a06a-3cf82f51c49c︡{"done":true}
︠4a2a49c0-6cc9-4669-bfab-294cf2e35b04︠

︡0d3f2ec9-5cf5-451f-bdde-fab8b91be480︡
︠8c1322fa-38db-459a-873d-27aa0210a387s︠
triangle(vector([0,0]), 0)
t1 = text("T = (a * b) / 2", (15,6));
t2 = text("4T = 2 * a * b", (15,4));
t3 = text("(a + b)^2 = 4T + c^2", (8, 14));
t4 = text("a^2 + 2 * a * b + b^2 = 2 * a * b + c^2", (8, 12));
t5 = text("a^2 + b^2 = c^2", (8, 10));

def t6 (c):
    if c < 8 :
        return text("", (2,10));
    else:
        return t3 + t4 + t5;

︡e658622b-8ebb-40a6-a362-6634f6901f72︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/1472/tmp_PS_P7h.svg","show":true,"text":null,"uuid":"93aac15e-e49e-45b7-b275-37bc963c76e3"},"once":false}︡{"done":true}
︠890bd7ae-9a05-438d-acec-996100a9a4a5s︠
myanim = [triangle(vector([0,0]), 0) + triangle(vector([5,0]) + c*vector([-5,7])/10, c*(pi/2)/10) + triangle(vector([10,0])+c*vector([-3,7])/10, c*pi/10) + triangle(vector([15,0])+c*vector([-8,0])/10, c*(pi*3/2)/10) + t1 + t2 + t6(c) for c in sxrange(0, 10.5, .5)]
a = animate(myanim, axes=True, aspect_ratio=1, xmin = -1, xmax =20, ymin=-2, ymax=15)
a.show(delay=10)
︡5af6510c-89d3-4d50-9e2c-952b91e1e0fb︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/1472/tmp_iKeFYV.webm","show":true,"text":null,"url":"/b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/raw/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/1472/tmp_iKeFYV.webm"},"once":false}︡{"done":true}
︠7c777d79-97ae-4a1b-8a7f-83354a78f1bbs︠
︡335d310f-aa2d-4022-ba47-705d8a3ade7e︡{"done":true}
︠e5dbed94-6d36-4336-925f-ace341531aed︠









