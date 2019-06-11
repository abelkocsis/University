︠481f81fa-d244-4e00-ac87-9db99d3d20acs︠
import random
def key_generation(q):
    #q = 20
    CG = CyclicPermutationGroup(q)
    g = CG.random_element()
    G = CG.subgroup([g])
    x = random.randint(1,q);
    h = g^x;
    public_key = (G,q,g,h);
    return (public_key, x);

def encryption(element_to_encrypt, (G,q,g,h)):
    m = element_to_encrypt;
    print(m);
    print("encrypted.");
    y = random.randint(1,q);
    s = h^y;
    c1 = g^y;
    c2 = m*s;
    return (c1, c2);
def decryption((c1, c2), x, (G,q,g,h)):
    s = c1^x;
    m = c2 * s^-1;
    print(m);
    print("decrypted.");



︡0387b40a-57ef-4700-9de3-208fa3394e31︡{"done":true}
︠9fd7d574-cd83-46c8-aa4f-99f6b1738ee6s︠

(public_key, private_key) = key_generation(20);
element_to_encrypt = public_key[0].random_element();
enc_mes = encryption(element_to_encrypt,public_key)
decryption(enc_mes, private_key, public_key)

︡a816146e-16ff-4075-87c9-fc483b6ea881︡{"stdout":"(1,11)(2,12)(3,13)(4,14)(5,15)(6,16)(7,17)(8,18)(9,19)(10,20)\nencrypted.\n"}︡{"stdout":"(1,11)(2,12)(3,13)(4,14)(5,15)(6,16)(7,17)(8,18)(9,19)(10,20)\ndecrypted.\n"}︡{"done":true}
︠bc65ab08-c35f-4e3a-8414-311b9037ac9fs︠
︡8d339caf-b5b0-4873-9ada-ed6b772418f8︡{"done":true}
︠d9448bc9-c8ad-4de7-bf40-93cadfaad9d2︠









