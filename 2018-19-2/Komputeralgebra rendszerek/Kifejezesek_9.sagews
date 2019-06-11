︠c9dd9359-fe03-44b7-ae2d-973ad15c5722s︠
import random
def Integral_alap(f, n):
    fmax = RR(f.find_local_maximum(-1,1)[0]).ceil();
    
    fmin = RR(f.find_local_minimum(-1,1)[0]).floor();
    
    show(fmin);

    p = plot(line([(-1,fmin), (-1,fmax)], color='blue'));
    p += plot(line([(1,fmin), (1,fmax)], color='blue'));

    p += plot(line([(-1,fmax), (1,fmax)], color='blue'));
    p += plot(line([(-1,fmin), (1,fmin)], color='blue'));

    p += plot(f, (f,-1,1), color='orange');

    jo = 0;
    rossz = 0;
    for i in xrange(1,n/2):
        if fmax > 0:
            x = random.randint(-10000, 10000)/10000;
            y = random.randint(max(0, fmin)*10000, fmax*10000)/10000;
            if f(x) >= 0 and y <= f(x):
                Pnt = point((x,y) , color='green');
                jo += 1;
            else:
                Pnt = point((x,y) , color='red');
            p += plot(Pnt);
        
        if fmin < 0 :
            x = random.randint(-10000, 10000)/10000;
            y = random.randint(fmin*10000, min(0, fmax)*10000)/10000;
            if f(x) <= 0 and y >= f(x):
                Pnt = point((x,y) , color='green');
                rossz += 1;
            else:
                Pnt = point((x,y) , color='red');
            p += plot(Pnt);
        
    show(p);
    kozelites = 0;
    if fmin > 0:
        kozelites = 2 * fmin;
    elif fmax < 0:
        kozelites = 2 * fmax;
    kozelites += 2 * (abs(fmax-max(0,fmin))) * (jo / (n/2));
    kozelites -= 2 * (abs(min(fmax, 0)-fmin)) * (rossz / (n/2));
    show (RR(kozelites));
︡6d38ee67-2f40-4411-9768-66ad91d27178︡{"done":true}
︠bae83ea3-59b4-42eb-ba19-cb61b3aa1040s︠
Integral_alap(x^3-4, 300)
︡5ef45ebe-b8fb-471f-a489-167f7d0b710b︡{"html":"<div align='center'>$\\displaystyle -5$</div>"}︡{"stderr":"<string>:1: DeprecationWarning: Substitution using function-call syntax and unnamed arguments is deprecated and will be removed from a future release of Sage; you can use named arguments instead, like EXPR(x=..., y=...)\nSee http://trac.sagemath.org/5930 for details.\n"}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/2213/tmp_VIV3_5.svg","show":true,"text":null,"uuid":"317973be-ee62-4b7a-b2f3-479a8e240ab1"},"once":false}︡{"html":"<div align='center'>$\\displaystyle -8.08000000000000$</div>"}︡{"done":true}
︠81ca93f0-7925-4cae-aceb-958a97f22cfas︠
Integral_alap(log(10) * x^3 - 3 * e^(x^5), 500)
︡099072a0-44ed-42be-bfcd-63a07f0cb7d4︡{"html":"<div align='center'>$\\displaystyle -4$</div>"}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/2213/tmp_Zd2ZcZ.svg","show":true,"text":null,"uuid":"7c3fb79f-48ed-4fbf-aa5b-ecd1738253c1"},"once":false}︡{"html":"<div align='center'>$\\displaystyle -6.28800000000000$</div>"}︡{"done":true}
︠1f74f052-75f4-46d8-9ed2-fcee22ee27c6s︠
Integral_alap(x^3, 300)


︡d9392c65-9ceb-4336-a3bf-8781698413cf︡{"html":"<div align='center'>$\\displaystyle -1$</div>"}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/316/tmp_Ep980k.svg","show":true,"text":null,"uuid":"dbafb5aa-8cc9-42bf-929b-0fe4732d3b7b"},"once":false}︡{"html":"<div align='center'>$\\displaystyle -0.0133333333333333$</div>"}︡{"done":true}
︠19360b2a-46dd-47b5-b2ca-05ad206dec3es︠
Integral_alap(x^3+1, 300)
︡b20580c9-7feb-46a5-a646-270c9016ce4a︡{"html":"<div align='center'>$\\displaystyle 0$</div>"}︡{"file":{"filename":"/home/user/.sage/temp/project-b26dead2-4fb8-48e9-8fb7-d1ddc44ea65b/316/tmp_nXd35U.svg","show":true,"text":null,"uuid":"9c39f317-628f-44ca-8aeb-c466e404beac"},"once":false}︡{"html":"<div align='center'>$\\displaystyle 2.05333333333333$</div>"}︡{"done":true}
︠8988906c-2fc2-440a-a2ea-dc830e6e9423︠

︡4f7c4b45-cc3a-41bc-a4ce-7ac9a939f270︡{"stdout":"0.036541625735247774\n"}︡{"done":true}
︠53e9637c-3b75-441e-bc96-0d29c052663e︠









