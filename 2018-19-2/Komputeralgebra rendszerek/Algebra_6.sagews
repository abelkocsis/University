︠b37de8ab-1b91-42d9-8df6-17d1ed6d26d3s︠
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
def broke ((c1, c2), (G,q,g,h)):
    m = 0;
    for a in xrange(1,q):
        try:
            s = c1^a;
            m = c2 * s^-1;
            if not h == g^a:
                continue;
        except:
            continue;
        else:
            print(m);
            print("broked.");
            print("Private key:");
            print(a);
            break;


︡14534d00-07c1-4987-aee4-eec94023ec72︡{"done":true}
︠9fd7d574-cd83-46c8-aa4f-99f6b1738ee6s︠
print("Keys generation");
(public_key, private_key) = key_generation(20);
print("Private key:");
private_key
print("Encryption:");
element_to_encrypt = public_key[0].random_element();
enc_mes = encryption(element_to_encrypt, public_key)

print("Breake:");
broke(enc_mes, public_key)
print("Checking - decryption:");
decryption(enc_mes, private_key, public_key)
︡b82d7893-cb40-49f6-a70a-163db0afb65c︡{"stdout":"Keys generation\n"}︡{"stdout":"Private key:\n"}︡{"stdout":"3\n"}︡{"stdout":"Encryption:\n"}︡{"stdout":"(1,13,5,17,9)(2,14,6,18,10)(3,15,7,19,11)(4,16,8,20,12)\nencrypted.\n"}︡{"stdout":"Breake:\n"}︡{"stdout":"(1,13,5,17,9)(2,14,6,18,10)(3,15,7,19,11)(4,16,8,20,12)\nbroked.\nPrivate key:\n3\n"}︡{"stdout":"Checking - decryption:\n"}︡{"stdout":"(1,13,5,17,9)(2,14,6,18,10)(3,15,7,19,11)(4,16,8,20,12)\ndecrypted.\n"}︡{"done":true}
︠a728b91e-3e1c-41f6-8861-6b9dc019e47c︠

︡d6baf4f9-8f42-400f-bdf4-612f79c829ac︡{"stdout":"(1,13,5,17,9)(2,14,6,18,10)(3,15,7,19,11)(4,16,8,20,12)\n"}︡{"done":true}
︠d1246401-86e7-4f14-9303-7e765e465a59︠









