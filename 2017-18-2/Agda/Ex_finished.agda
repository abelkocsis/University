{-# OPTIONS --rewriting #-}

module Ex where

open import lib

-- Propositional logic

-- _→_

l1 : X → X
l1 = λ x → x

l2 : X → Y → X
l2 = λ x → λ y → x

l3 : (X → Y) → X
l3 =  λ x → {! !} -- Ezt nem lehet bizonyatani.

l4 : X → Y → Y
l4 =  λ x y → y

l5 : X → X → X
l5 =  λ x x' → x

l5' : X → X → X
l5' =  λ x x' → x' 

l6 : (X → Y → Z) → (Y → X → Z)
l6 =  λ x →  λ y z → x z y

l6b : (X → Y) → (Y → Z) → (X → Z)
l6b =  λ x y z →  y (x z)

l6c : (Y → Z) → (X → Y) → (X → Z)
l6c =  λ x y z →  x (y z)

l6d : (X → X → Y) → (X → Y)
l6d =  λ x y → x y y

l6e : (X → Y) → (X → X → Y)
l6e =  λ x y z → x y

l6f : (X → Y) → (X → X → Y)
l6f =  λ x y z → x z

l16g : (X → Y) → (X → Y)
l16g = λ x y → x y

-- ⊤

l7 : ⊤
l7 = tt

l8 : X → ⊤
l8 =  λ x → tt

l8b : ⊤ → ⊤
l8b =  λ x → tt

-- ⊥

l9 : ⊥ → X
l9 =  λ x → abort x

l9b : (X → ⊥) → (X → Y)
l9b =  λ x y →  abort (x y)

l9c : (⊤ → ⊥) → ⊥
l9c =  λ x → x tt

-- ¬_

l10 : X → ¬ ¬ X
l10 =  λ x y → y x

l11 : ¬ ¬ (¬ ¬ X → X)
l11 =  λ x →  x λ y → abort ( y  λ z → x λ v → z)

l12 : ¬ ¬ ¬ X → ¬ X
l12 =  λ x y →  x λ z →  z y

l13 : ¬ X → ¬ ¬ ¬ X
l13 = λ x y → y x

-- _×_

l14 : (X → Y) × (Y → Z) → (X → Z)
l14 =  λ x y →  proj₂ x ( proj₁ x y)

l15 : ((X × Y) × Z) → (X × (Y × Z))
l15 =  λ x →  proj₁ (proj₁ x) , (proj₂ (proj₁ x) , proj₂ x)

l16 : (X → (Y × Z)) → ((X → Y) × (X → Z))
l16 =  λ x →  (λ y → proj₁ (x y)) , λ y → proj₂ (x y)

l16' : (X × Y → Z) → Y × (Y → X) → Z
l16' =  λ x y → x ( proj₂ y (proj₁ y) , proj₁ y)

-- _↔_

l19 : X ↔ X × ⊤
l19 =  (λ x → x , tt) , λ x → proj₁ x

l17 : ¬ ¬ ¬ X ↔ ¬ X
l17 =  (λ x y → x λ z → z y) ,  λ x y → y x

l18 : ¬ (X ↔ ¬ X)
l18 =  λ x →  proj₁ x (proj₂ x (λ y → proj₁ x y y)) ( proj₂ x λ y → proj₁ x y y)

-- _⊎_

l21 : X ⊎ X → X
l21 =  λ x →  case x (λ y → y)  λ y → y

l22 : (X × Y) ⊎ Z → (X ⊎ Z) × (Y ⊎ Z)
l22 =  λ y → case y (λ x →  inj₁ (proj₁ x) , inj₁ (proj₂ x)) λ x →   inj₂ x , inj₂ x

l20 : X ↔ X ⊎ ⊥
l20 =  (λ x → inj₁ x) , λ x → case x (λ y → y)  λ y → case x (λ z → z) ( case x (λ z v → z)  λ z v → abort v)

l23 : (Y ⊎ X) ↔ (X ⊎ Y)
l23 =   (λ x → case x (λ y → inj₂ y) λ y → inj₁ y) ,  λ x →  case x (λ x → inj₂ x) λ y → inj₁ y
 
l24 : (X ⊎ Y → Z) → (X → Z) × (Y → Z)
l24 =  λ x →  (λ y → x (inj₁ y)) ,  λ y → x (inj₂ y)

l25 : ¬ ¬ (X ⊎ ¬ X)
l25 = λ x → x (inj₂ λ y → x (inj₁ y))

l26 : (¬ X ⊎ Y) → X → Y
l26 =  λ x y → case x (λ z → abort (z y)) λ z → z

l27 : ¬ (X ⊎ Y) ↔ (¬ X × ¬ Y)
l27 =  (λ x → (λ y → x (inj₁ y)) ,  λ y → x (inj₂ y)) ,  λ x y → case y (proj₁ x) (proj₂ x)

l28 : (¬ X ⊎ ¬ Y) → ¬ (X × Y)
l28 =  λ x y →  case x (λ z →  z (proj₁ y)) λ z → z (proj₂ y)


-- Propositions as types

-- define all different elements of the following sets

e1 : ⊤ × ⊤
e1 =  tt , tt

e2 : ⊤ ⊎ (⊤ ⊎ ⊤)
e2 =  inj₁ tt

e2' : ⊤ ⊎ (⊤ ⊎ ⊤)
e2' =  inj₂ (inj₁ tt)

e2'' : ⊤ ⊎ (⊤ ⊎ ⊤)
e2'' = inj₂ ( inj₂ tt)

-- defining booleans and operations of booleans

Bool : Set
Bool = ⊤ ⊎ ⊤

true false : Bool
true =  inj₁ tt
false =  inj₂ tt

-- you can ignore {C : Set} for now
if_then_else_ : {C : Set} → Bool → C → C → C
if_then_else_ =  λ x y z →  case x (λ v → y)  λ v → z

not : Bool → Bool
not =  λ x → case x (λ y → inj₂ tt) λ y → inj₁ tt

and : Bool → Bool → Bool
and =  λ x y →  case x ( case y ( λ z v → inj₁ tt) λ z v → inj₂ tt) λ z → inj₂ tt

or : Bool → Bool → Bool
or =  λ x y →  case x ( λ z →  inj₁ tt) ( case y ( λ z v → inj₁ tt) λ v z → inj₂ tt)

xor : Bool → Bool → Bool
xor =  λ x y →  case x ( case y ( λ z v →  inj₂ tt) ( λ z v → inj₁ tt)) ( case y ( λ z v → inj₁ tt) λ x z → inj₂ tt)

-- test the above definitions by C-c C-n

-- define all the elements of Bool × Bool!

bb1 bb2 bb3 bb4 : Bool × Bool
bb1 =  inj₁ tt , inj₁ tt
bb2 =  inj₁ tt ,  inj₂ tt
bb3 =  inj₂ tt , inj₁ tt
bb4 =  inj₂ tt , inj₂ tt

-- all the functions from the three-element set to Bool

Three : Set
Three = ⊤ ⊎ ⊤ ⊎ ⊤

eight1 eight2 eight3 eight4 eight5 eight6 eight7 eight8 : Three → Bool
eight1 = {! !}
eight2 = {!!}
eight3 = {!!}
eight4 = {!!}
eight5 = {!!}
eight6 = {!!}
eight7 = {!!}
eight8 = {!!}

-- define a case operation on the three-element set!

case3 : {C : Set} → Three → C → C → C → C
case3 = {! !}

-- Peano

two three : ℕ
two =  suc (suc zero)
three =  suc two

seven : ℕ
seven = suc (suc (suc (suc three)))

-- 0 ↦ 1
-- 1 ↦ 3
-- 2 ↦ 5
-- 3 ↦ 7
-- 4 ↦ 9

2*_+1 : ℕ → ℕ
2*_+1 = λ x → rec (suc zero) (λ y → suc (suc y)) x
{-
  2* three 1+
= 2*_1+ three
= (λ n → rec (suc zero) (λ x → suc (suc x)) n) three
  (λ x → t                                   ) u
  t[x ↦ u]
= rec (suc zero) (λ x → suc (suc x)) three
= rec (suc zero) (λ x → suc (suc x)) (suc (suc (suc zero)))
= (λ x → suc (suc x)) (rec (suc zero) (λ x → suc (suc x)) (suc (suc zero)))
= suc (suc (rec (suc zero) (λ x → suc (suc x)) (suc (suc zero))))
= suc (suc ((λ x → suc (suc x)) (rec (suc zero) (λ x → suc (suc x)) (suc zero))))
= suc (suc ((λ x → suc (suc x)) (rec (suc zero) (λ x → suc (suc x)) (suc zero))))
= suc (suc (suc (suc (rec (suc zero) (λ x → suc (suc x)) (suc zero)))))
= suc (suc (suc (suc (suc (suc (rec (suc zero) (λ x → suc (suc x)) zero))))))
= suc (suc (suc (suc (suc (suc (suc zero))))))
-}

-- check the result of 2* three +1 using C-c C-n

2*_+1' : ℕ → ℕ
2*_+1' =  λ n → rec ( suc zero)  (λ i → suc ( suc i))  n

-- check the result of 2* three +1' using C-c C-n

four five : ℕ
four = suc three
five = suc four

3*_+5 : ℕ → ℕ
3*_+5 =  λ n → rec (suc (suc (suc (suc (suc zero)))))  (λ x →  (suc (suc (suc x)))) n

-- test the result of 3* four +5
-- test the result of 3* zero +5

_+_ : ℕ → ℕ → ℕ
_+_ =  λ m n → rec n  (λ x → (suc x)) m

infixl 5 _+_

-- test the result of four + five
-- test the result of five + four
-- test the result of five + three

_*_ : ℕ → ℕ → ℕ
_*_ =   λ m n → rec zero  (λ x →  x + n) m

infixl 6 _*_

-- equality

seventeen : ℕ
seventeen = five + five + five + suc (suc zero)

test1 : 3* four +5 ≡ seventeen
test1 =  refl (3* four +5)

test2 : four + five ≡ five + four
test2 =  refl (four + five)

six : ℕ
six = suc five

test3 : three * six ≡ seven + seven + four
test3 =  refl (three * six)

test4 : three * four ≡ six + six
test4 =  refl (three * four)

twistedTrans : {x y z : ℕ} → x ≡ y → z ≡ x → y ≡ z
twistedTrans =  λ x y →  trans (sym x) (sym y)

-- universal quantification

--                   rec n (λ x → suc x) zero = n
leftunit : (n : ℕ) → zero + n ≡ n
leftunit =  λ n →  refl n

suc-congruence : (a b : ℕ) → a ≡ b → suc a ≡ suc b
suc-congruence =  λ n m x →  cong suc x

+5-congruence : (a b : ℕ) → a ≡ b → a + five ≡ b + five
+5-congruence =  λ x y →  λ z → cong (rec (suc (suc (suc (suc (suc zero))))) suc) z

twistedTrans' : (A : Set)(x y z : A) → x ≡ y → z ≡ x → y ≡ z
twistedTrans' =  λ x y z →  λ v w e →  trans (sym w) (sym e)

-- predicates

P : ℕ → Set
P = λ n → n + two ≡ three

pone : P (suc zero) -- = (n + two ≡ three)[n ↦ suc zero] = (three ≡ three)
pone = cong ( λ x → (suc (suc (suc x)))) (refl zero)

-- induction

--                    rec zero (λ x → suc x) n
rightunit : (n : ℕ) → n + zero ≡ n
rightunit =   λ n → ind (λ i →  i + zero ≡ i) (refl zero)  (λ x y → cong suc y) n

assoc : (a b c : ℕ) → (a + b) + c ≡ a + (b + c)
assoc =  λ p q r → ind ( λ i → ((i + q) + r ≡ i + (q + r) )) ( refl (rec r suc q)) ( λ p₁ → ( λ x →  cong (suc) (x))) p

same : (n : ℕ) → rec zero suc n ≡ n
same =  λ n → ind ( λ m →  rec zero suc m ≡ m) (refl zero) ( λ m x →  cong suc x) n

sucright : (a b : ℕ) → a + suc b ≡ suc (a + b)
sucright =  λ m n → ind  (λ i →  i + suc n ≡ suc (i + n)) ( refl (suc n)) ( λ p x →  cong suc x) m

comm : (a b : ℕ) → a + b ≡ b + a -- use rightunit, sucright, sym, trans, cong, EZ A  LEGNEHEZEBB
 -- comm =  λ n m → ind  (λ a → ( a + m ≡ m + a)) (sym (same m)) (λ n₁ h → trans ( cong suc h) ( sym (sucright m n₁)))  n

comm = λ m n → ind  (λ i → (i + n ≡ n + i)) ( sym (same n)) ( λ p x → trans ( cong suc x) (sym (sucright n p))) m




-- define sym, trans and cong using subst

sym' : (A : Set)(x y : A) → x ≡ y → y ≡ x
sym' =   λ A x y T → subst ( λ i → i ≡ x) T ( refl x)

trans' : (A : Set)(a a' a'' : A) → a ≡ a' → a' ≡ a'' → a ≡ a''
trans' =  λ A a a' a'' I J → subst ( λ i → a ≡ i)  J  I

cong' : (A B : Set)(f : A → B)(a a' : A) → a ≡ a' → f a ≡ f a'
cong' =  λ A B f a a' T → subst  (λ i → f a ≡ f i)  T (refl (f a))

-- define a predicate s.t. Q zero = ⊤ and Q (suc n) = ⊥

Q : ℕ → Set
Q  = rec ⊤ λ x → ⊥

-- show that zero is not equal to one

_≢_ : {A : Set} → A → A → Set
_≢_ = λ x y → ¬ (x ≡ y)

0≢1 : zero ≢ suc zero
0≢1 = λ x → subst Q  x tt
-- similarly show that true is not equal to false. use case instead of
-- if_then_else_

-- false-hez topot, true-hoz bottomot


W : Bool → Set
W = λ x → case x (λ y → ⊤) λ y → ⊥

true≢false : true ≢ false
true≢false =  λ x → subst W x tt

-- predicate logic

l3b : ¬ ((X Y : Set) → (X → Y) → X) -- Ez kell
l3b =  λ x →  x  ⊥  ⊥ λ x → x

comp : (A : Set)(B : A → Set)(C : (x : A) → B x → Set)
       (f : (x : A) → B x) → ((x : A) → (y : B x) → C x y)
     → (x : A) → C x (f x)
comp = λ x y → λ z v →  λ w → λ a →  w a (v a)

pred1 : {M : Set}{P Q : M → Set}
      → ((x : M) → P x × Q x) ↔ ((x : M) → P x) × ((x : M) → Q x)
pred1 =  (λ x →  (λ y →  proj₁ (x y)) , λ y → proj₂ (x y)) , λ x → λ y →   (proj₁ x) y ,  (proj₂ x) y

pred2 : {M : Set}{P : M → Set}
      → ¬ ¬ ((x : M) → P x) → (x : M) → ¬ ¬ (P x)
pred2 =  λ x y →  λ z → x λ v →  z (v y)

-- Σ

l3c : Σ Set λ X → Σ Set λ Y → (X → Y) → X
l3c = ⊤ ∙ (⊥ ∙ λ x → tt)

pred3 : {M : Set}{P : M → Set}
   → (Σ M λ x → ¬ P x) → ¬ (∀(x : M) → P x)
pred3 = λ x x₁ →  (pr₂ x) ( x₁ (pr₁ x))

pred4 : {M : Set}{P : M → Set}
   → (¬ Σ M λ x → P x) → ∀(x : M) → ¬ P x
pred4 =  λ x y z → x ( y ∙ z)

pred5 : {M : Set}{P : M → Set}
   → ((x : M) → ¬ P x) → ¬ Σ M λ x → P x
pred5 =  λ x y →  x ( pr₁ y) ( pr₂ y)

pred6 : {M N : Set}{R : M → N → Set}
   → (Σ M λ x → ∀(y : N) → R x y) → ∀(y : N) → Σ M λ x → R x y
pred6 =  λ x y →   pr₁ x ∙  (pr₂ x) y 

-- axiom of choice

AC : {M N : Set}{R : M → N → Set}
   → ((x : M) → Σ N λ y → R x y) → Σ (M → N) λ f → (x : M) → R x (f x)
AC =  λ x →  ( λ y →  pr₁ (x y)) ∙  λ y →  pr₂ (x y) 

-- decidability

Decidable : Set → Set
Decidable = λ A → A ⊎ ¬ A

-- if every set is decidable (law of excluded middle), we have:

dec1 : (lem : (A : Set) → Decidable A) → (A : Set) → ¬ ¬ A → A
dec1 =  λ x y z →   case (x y) λ x → x  λ v → abort (z v)
-- Innen már nem kell

module _ (lem : (A : Set) → Decidable A)(M : Set)(P : M → Set) where

  dec2 : ¬ (X × Y) → (¬ X ⊎ ¬ Y) -- Ezeknél valamilyen case kell?
  dec2 =  λ x →  case (lem M)  λ T → {! !}  λ y → {!!}

  Peirce : ((X → Y) → X) → X
  Peirce = {!!}

  dec3 : (¬ ¬ X ⊎ Y) → ¬ Y → X
  dec3 = {!!}

  dec4 : (¬ Σ M λ x → ¬ P x) → (x : M) → P x
  dec4 = {!!}

  Nonempty : Set → Set
  Nonempty = λ M → Σ M λ x → ⊤

  -- use dec4!
  pub : Nonempty M → Σ M λ m → P m → (x : M) → P x
  pub = {!!}

  -- use dec4!
  dec5 : (¬ (∀(x : M) → P x)) → Σ M λ x → ¬ P x
  dec5 = {!!}
