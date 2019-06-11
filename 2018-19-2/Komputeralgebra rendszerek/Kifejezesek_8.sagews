︠99e5d8f6-52bc-4abc-9d22-c3b1ea4e55d8s︠
import random
def Kozelites_alap(n):
    p = plot(line([(-1,-1), (-1,1)], color='black'));
    p += plot(line([(-1,1), (1,1)], color='black'));
    p += plot(line([(1,1), (1,-1)], color='black'));
    p += plot(line([(-1,-1), (1,-1)], color='black'));
    p += plot (circle((0,0), 1, color='orange'));
    jo = 0;
    for i in xrange(1,n):
        x = random.randint(-10000,10000)/10000;
        y = random.randint(-10000,10000)/10000;
        if x * x + y * y <= 1:
            Pnt = point((x,y) , color='green');
            jo += 1;
        else:
            Pnt = point((x,y) , color='red');
        p += plot(Pnt);
    show(p);
    kozelites = 4 * (jo / n);
    show (RR(kozelites));

︡6081e461-038d-4adb-bedd-7e2746e40bba︡{"done":true}
︠cae8aed8-7e42-41de-b818-0662e5fee664s︠
import random
def Kozelites(n):
    p2 = plot(0, title='Kozelitett terulet');
    p3 = plot(0, title='Kozelites hibaja');
    p1 = plot(line([(-1,-1), (-1,1)], color='black', ));
    p1 += plot(line([(-1,1), (1,1)], color='black', title='A pontok elhelyezkedese'));
    p1 += plot(line([(1,1), (1,-1)], color='black'));
    p1 += plot(line([(-1,-1), (1,-1)], color='black'));
    p1 += plot (circle((0,0), 1, color='orange'));
    jo = 0;
    for i in xrange(1,n):
        x = random.randint(-10000,10000)/10000;
        y = random.randint(-10000,10000)/10000;
        if x * x + y * y <= 1:
            Pnt = point((x,y) , color='green');
            jo += 1;
        else:
            Pnt = point((x,y) , color='red');
        p1 += plot(Pnt);
        kozelites = (4 * (jo / i));
        p2 += point((i, kozelites))
        p3 += point((i, abs(kozelites-pi)))
    show(p1);
    show(p2);
    show(p3);

︡4fc05bc0-c3dc-465f-ba4c-ae924a808205︡{"done":true}
︠19c34ab5-12e4-4674-a4de-b7ea6bdb8492︠

︡75930201-447d-4d4d-8993-6c804206d8eb︡
︠51752b10-8f34-4059-abaf-4c78f6260145s︠
Kozelites_alap(10)
︡b37fbe96-7fe8-42bf-a231-960b944e8f0f︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/452/tmp_FOkX0u.svg","show":true,"text":null,"uuid":"7334b66d-37e6-4597-a449-5e1e42b11c70"},"once":false}︡{"html":"<div align='center'>$\\displaystyle 3.20000000000000$</div>"}︡{"done":true}
︠34f78c0b-9f90-4445-b1cc-9f8ee4ce3ba1s︠
Kozelites_alap(40)
︡fed5f3fb-4f48-4322-9a75-94ed502829f7︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp_d98xK_.svg","show":true,"text":null,"uuid":"7ab9e77e-4c26-45ea-8ddc-a4d56000bc03"},"once":false}︡{"html":"<div align='center'>$\\displaystyle 3.10000000000000$</div>"}︡{"done":true}
︠2021de7a-9047-4ed3-bcc9-f1e78be3f9eb︠

︡d0fdff50-1bb7-41e4-ab69-95e80580900e︡
︠bd5ad56e-c43e-4bf4-bdff-08bf6007f04bs︠
Kozelites_alap(100)
︡c7b8df7d-216b-4099-b5ed-e49cec560dd6︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp_y0zwAo.svg","show":true,"text":null,"uuid":"5fa73cd3-0d15-4384-9099-f8bb2cd46de0"},"once":false}︡{"html":"<div align='center'>$\\displaystyle 3.04000000000000$</div>"}︡{"done":true}
︠f48f1529-5069-4c08-b6dc-7dedb28e5886s︠
Kozelites(100)
︡6759c894-d173-4f87-8bd5-e438f7b2d40f︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp__raEiU.svg","show":true,"text":null,"uuid":"bb4c23b1-876d-4c80-93c9-9dd88a16e601"},"once":false}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp__2xvUb.svg","show":true,"text":null,"uuid":"7c5304d5-9c21-4f44-8e03-f8748fead470"},"once":false}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp_DQNPfX.svg","show":true,"text":null,"uuid":"5dfe2090-1e12-4e92-a2ff-02d5b6863bcf"},"once":false}︡{"done":true}
︠6814d836-1aba-4fd2-9435-35ff5dec352as︠
Kozelites(250)
︡0f504978-bea9-4045-b116-5e40d08409ad︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp_BBtgXq.svg","show":true,"text":null,"uuid":"202c9f5c-19c2-48d9-a72b-b464c257ebe3"},"once":false}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp_ZHvLlp.svg","show":true,"text":null,"uuid":"287a2ce4-217c-4abb-b36c-766f5bec6248"},"once":false}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/319/tmp_rHYYsA.svg","show":true,"text":null,"uuid":"fcca3c57-b14f-4d04-9501-db4e31f9b79f"},"once":false}︡{"done":true}
︠ce75e209-47c2-4e90-bad6-425cae94f9e0︠









