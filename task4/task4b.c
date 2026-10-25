#include <stdio.h>
typedef long long ll;
/*
1. select p,q
2. n = p * q
3. phi = (p-1) * (q-1)
4. choose e : 1 < e < phi such that gcd(e,phi) = 1
5. choose d such that :
(d * e) =~ 1 (mod phi)
6. ciphertext = pow(message,e) (mod n)
   plaintext = pow(ciphertext,d) (mod n)
*/

ll mod_inverse(ll a, ll m)
{
    a = a % m;

    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1;
}

ll power(ll a, ll b, ll mod)
{
    ll res = 1;
    a = a % mod;
    while (b)
    {
        if (b % 2)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

ll gcd(ll a, ll b)
{
    while (b)
    {
        ll tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main()
{
    ll p = 61, q = 53;
    ll n = p * q;
    ll phi = (p - 1) * (q - 1); // 3120
    ll e = -1;
    for (ll i = 2; i < phi; i++)
    {
        if (gcd(phi, i) == 1)
        {
            e = i;
            break;
        }
    }

    ll d = mod_inverse(e, phi);
    ll message = 65; // Alphabet A
    if (e != -1 && d != -1)
    {
        ll ciphertext = power(65, e, n);
        ll plaintext = power(ciphertext, d, n);
        printf("Message: %lld\n", message);
        printf("Ciphertext: %lld\n", ciphertext);
        printf("Plaintext: %lld\n", plaintext);
    }
}