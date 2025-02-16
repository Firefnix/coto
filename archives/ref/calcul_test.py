from unittest import TestCase, main
from calcul import zero, un, Naturel, Relatif, Rationnel, Puissance, \
    sqrt, Complexe, i, F2, F2Uplet, int_log2, int_vers_bin, bin_vers_int, \
    strbin_vers_int, int_vers_strbin, Matrice, VectPi, pi, Expi, expi, Somme, \
    somme

class TestZero(TestCase):
    def test_sous(self):
        assert zero.sous() == zero

    def test_sur(self):
        assert zero.sur(Naturel) == Naturel(0)
        assert zero.sur(Relatif) == Relatif(0)
        assert zero.sur(Rationnel) == Rationnel(0, 1)

    def test_plus(self):
        trois = Naturel(3)
        assert zero + zero == zero
        assert trois + zero == trois
        assert zero + trois == trois

    def test_fois(self):
        trois = Naturel(3)
        moins_trois = Relatif(-3)
        un_tiers = Rationnel(1, 3)
        assert zero * zero == zero
        assert zero * trois == zero
        assert trois * zero == zero
        assert zero * moins_trois == zero
        assert moins_trois * zero == zero
        assert zero * un_tiers == zero
        assert un_tiers * zero == zero

    def test_signe(self):
        assert zero.signe() == 1

    def test_pow(self):
        assert zero ** 3 == zero ** un == zero
        assert zero ** zero == un

    def test_arg(self):
        assert zero.arg() == zero

    def test_conjugue(self):
        assert zero.conjugue() == zero


class TestNaturels(TestCase):
    def test_sous(self):
        trois = Naturel(3)
        z = Naturel(0)
        assert trois.sous() == trois
        assert z.sous() == zero

    def test_sur(self):
        deux = Naturel(2)
        assert deux.sur(Relatif) == Relatif(2)
        assert deux.sur(Rationnel) == Rationnel(2, 1)
        assert deux.sur(Puissance) == Puissance(2, 1)
        assert deux.sur(Complexe) == Complexe(deux, zero)

    def test_plus(self):
        deux = Naturel(2)
        trois = Naturel(3)
        cinq = Naturel(5)
        assert deux + trois == cinq
        assert trois + deux == cinq

    def test_fois(self):
        deux = Naturel(2)
        trois = Naturel(3)
        six = Naturel(6)
        assert deux * trois == six
        assert trois * deux == six
        assert deux * trois == deux * 3

    def test_neg(self):
        assert (- un) == Relatif(-1)
        assert (- Naturel(3)) == Relatif(-3)

    def test_abs(self):
        assert abs(Naturel(2)) == Naturel(2)

    def test_div(self):
        assert Naturel(6) / Naturel(2) == Naturel(3)
        assert (un*6) / 2 == (un*3)

    def test_mod(self):
        quinze = Naturel(15)
        assert quinze % Naturel(3) == quinze % 3 == zero
        assert quinze % Naturel(6) == quinze % 6 == Naturel(3)

    def test_floordiv(self):
        quinze = Naturel(15)
        assert quinze // Naturel(3) == quinze // 3 == Naturel(5)
        assert quinze // Naturel(6) == quinze // 6 == Naturel(2)

    def test_signe(self):
        assert Naturel(3).signe() == 1

    def test_pow(self):
        deux, trois = Naturel(2), Naturel(3)
        assert deux ** 3 == deux ** trois == Naturel(8)
        assert deux ** (-3) == deux ** (-trois) == Rationnel(1, 8)

    def test_arg(self):
        assert Naturel(2).arg() == zero

    def test_conjugue(self):
        assert Naturel(3).conjugue() == Naturel(3)


class TestRelatifs(TestCase):
    def test_sous(self):
        moins_trois = Relatif(-3)
        trois = Relatif(3)
        z = Relatif(0)
        assert z.sous() == zero
        assert trois.sous() == Naturel(3)
        assert moins_trois.sous() == moins_trois

    def test_plus(self):
        deux = Relatif(2)
        trois = Relatif(-3)
        moins_un = Relatif(-1)
        assert deux + trois == moins_un
        assert trois + deux == moins_un

    def test_fois(self):
        deux = Relatif(2)
        moins_trois = Relatif(-3)
        moins_six = Relatif(-6)
        assert deux * moins_trois == moins_six
        assert moins_trois * deux == moins_six
        assert un * (-3) == moins_trois

    def test_neg(self):
        assert (- Relatif(-2)) == Naturel(2)
        assert (- Relatif(2)) == Relatif(-2)

    def test_abs(self):
        assert abs(Relatif(-2)) == Naturel(2)

    def test_div(self):
        assert Relatif(-2) / Relatif(3) == Rationnel(-2, 3)
        assert Relatif(-2) / Relatif(-3) == Rationnel(2, 3)

    def test_mod(self):
        moins_quinze = Relatif(-15)
        assert moins_quinze % Relatif(-3) == moins_quinze % (-3) == zero
        assert moins_quinze % Relatif(-6) == moins_quinze % (-6) == Relatif(-3)

    def test_floordiv(self):
        moins_quinze = Relatif(-15)
        assert moins_quinze // Relatif(-3) == moins_quinze // (-3) == Naturel(5)
        assert moins_quinze // Relatif(-6) == moins_quinze // (-6) == Naturel(2)

    def test_signe(self):
        assert Relatif(3).signe() == 1
        assert Relatif(-3).signe() == -1

    def test_pow(self):
        moins_deux, trois = Relatif(-2), Naturel(3)
        assert moins_deux ** 3 == moins_deux ** trois == Relatif(-8)
        assert moins_deux ** (-3) == moins_deux ** (-trois) == Rationnel(-1, 8)

    def test_arg(self):
        assert Relatif(2).arg() == zero
        assert Relatif(-2).arg() == pi

    def test_conjugue(self):
        assert Relatif(-2).conjugue() == Relatif(-2)


class TestRationnels(TestCase):
    def test_sous(self):
        assert Rationnel(0, 3).sous() == zero
        assert Rationnel(6, 2).sous() == Naturel(3)
        assert Rationnel(-6, 2).sous() == Relatif(-3)

    def test_eq(self):
        assert Rationnel(2, 6) == Rationnel(1, 3)
        assert Rationnel(1, -3) == Rationnel(-1, 3)
        assert Rationnel(-1, -3) == Rationnel(1, 3)

    def test_neg(self):
        assert (- Rationnel(1, 3)) == Rationnel(-1, 3)
        assert (- (- Rationnel(1, 3))) == Rationnel(1, 3)

    def test_plus(self):
        un_demi = Rationnel(1, 2)
        moins_un_tiers = Rationnel(-1, 3)
        un_sixieme = Rationnel(1, 6)
        assert un_demi + un_demi == un
        assert un_demi + (-un_demi) == zero
        assert un_demi + moins_un_tiers == un_sixieme

    def test_fois(self):
        deux_tiers = Rationnel(2, 3)
        trois_quarts = Rationnel(3, 4)
        un_demi = Rationnel(1, 2)
        assert deux_tiers * trois_quarts == un_demi
        assert trois_quarts * deux_tiers == un_demi
        assert Relatif(-2) * un_demi == Relatif(-1)
        assert un_demi * Relatif(-2) == Relatif(-1)

    def test_div(self):
        assert un / 5 == Rationnel(1, 5)
        assert Rationnel(1, 3) / Rationnel(4, 3) == un / 4

    def test_abs(self):
        assert abs(Rationnel(1, 2)) == Rationnel(1, 2)
        assert abs(Rationnel(-1, 2)) == Rationnel(1, 2)

    def test_signe(self):
        assert (un / 2).signe() == 1
        assert Rationnel(-1, 2).signe() == -1
        assert Rationnel(2, 1).signe() == 1

    def test_arg(self):
        assert (un / 2).arg() == zero
        assert (-un / 2).arg() == pi

    def test_conjugue(self):
        assert (un / 2).conjugue() == (un / 2)


class TestPuissance(TestCase):
    def test_sous(self):
        assert Puissance(4, Rationnel(1, 2)).sous() == Naturel(2)
        assert Puissance(Rationnel(1, 1), Rationnel(1, 1)) == un

    def test_eq(self):
        x = Puissance(2, Rationnel(2, 3))
        y = Puissance(4, Rationnel(1, 3))
        z = Puissance(un / 2, -un / 2)
        assert x == y
        assert z == sqrt(2)

    def test_sqrt(self):
        assert sqrt(2) == Puissance(2, Rationnel(1, 2))
        assert sqrt(5) == Puissance(5, Rationnel(1, 2))
        assert sqrt(4) == Naturel(2)

    def test_fois(self):
        d = un / 2
        x = Puissance(d, d, -1)
        y = Puissance(d, Rationnel(3, 2))
        z = Puissance(d, -d)
        assert sqrt(2) * sqrt(2) == Naturel(2)
        assert sqrt(2) * sqrt(d) == sqrt(d) * sqrt(2) == un
        assert sqrt(d) * sqrt(d) == d
        assert un * sqrt(2) == sqrt(2) * un == sqrt(2)
        assert Relatif(-1) * sqrt(d) == sqrt(d) * Relatif(-1) == x
        assert y * (-2) == -sqrt(d)
        print(z * sqrt(8))
        assert z * sqrt(8) == un * 4
        assert sqrt(8) * z == un * 4


    def test_pow(self):
        assert sqrt(2) ** 2 == Naturel(2)
        assert sqrt(un / 2) ** (-2) == Naturel(2)

    def test_neg(self):
        assert - Puissance(5, Rationnel(1, 2)) == Puissance(5, Rationnel(1, 2), -1)
        assert - Puissance(5, Rationnel(1, 2), -1) == Puissance(5, Rationnel(1, 2))

    def test_abs(self):
        assert abs(- sqrt(7)) == sqrt(7)

    def test_inverse(self):
        assert sqrt(2).inverse() == sqrt(Rationnel(1, 2))

    def test_signe(self):
        assert sqrt(2).signe() == 1
        assert (-sqrt(2)).signe() == -1

    def test_arg(self):
        assert sqrt(2).arg() == zero
        assert (-sqrt(2)).arg() == pi

    def test_conjugue(self):
        assert sqrt(3).conjugue() == sqrt(3)


class TestComplexe(TestCase):
    def test_plus(self):
        z1 = Complexe(1, -2)
        z2 = Complexe(-2, 1)
        z3 = Complexe(-1, -1)
        assert z1 + z2 == z3

    def test_fois(self):
        z1 = Complexe(un, Relatif(-2))
        z2 = Complexe(Relatif(-2), un)
        z3 = Complexe(zero, Naturel(5))
        assert z1 * z2 == z3
        assert i * (-i) == un

    def test_neg(self):
        z = Complexe(un, Relatif(-2))
        moins_z = Complexe(Relatif(-1), Naturel(2))
        assert (- z) == moins_z

    def test_abs(self):
        z = Complexe(un, Relatif(-2))
        assert abs(z) == sqrt(5)
        assert abs(i) == un

    def test_sous(self):
        assert Complexe(2).sous() == Naturel(2)
        assert Complexe(-6).sous() == Relatif(-6)
        assert Complexe(un / 2).sous() == (un / 2)
        assert Complexe(sqrt(2)).sous() == sqrt(2)

    def test_sur(self):
        assert (i + 1).sur(Expi) == Expi(pi / 4, module=sqrt(2))
        assert ((-i + 1) / sqrt(2)).sur(Expi) == Expi(- pi / 4)

    def test_arg(self):
        assert (i * 5).arg() == pi / 2
        assert (-i * 2).arg() == -pi / 2
        assert (i - 1).arg() == (pi * 3) / 4
        assert (-i + 1).arg() == -pi / 4
        assert Complexe(-6, 0).arg() == pi
        assert Complexe(6, 0).arg() == zero

    def test_conjugue(self):
        z = Complexe(un, Relatif(-2))
        z_barre = Complexe(un, Naturel(2))
        assert z.conjugue() == z_barre
        assert sqrt(2).sur(Complexe).conjugue() == sqrt(2)


class TestF2(TestCase):
    def test_sous(self):
        z = F2(0)
        u = F2(1)
        assert z.sous() == z
        assert u.sous() == u

    def test_int(self):
        assert int(F2(1)) == int(F2(5)) == 1
        assert int(F2(0)) == int(F2(8)) == 0

    def test_calcul(self):
        assert F2(F2(1)) == F2(1)
        assert F2(0) == F2(zero) == F2(Rationnel(8, 4))
        assert F2(1) == F2(un) == F2(Rationnel(9, 3))

    def test_sur(self):
        z = F2(0)
        u = F2(1)
        assert z.sur(Naturel) == Naturel(0)
        assert u.sur(Naturel) == un

    def test_plus(self):
        z = F2(0)
        u = F2(1)
        assert z + z == u + u == z
        assert z + u == u + z == u
        assert z + 0 == u + 1 == z
        assert z + 1 == u + 0 == u

    def test_fois(self):
        z = F2(0)
        u = F2(1)
        assert z * z == z
        assert z * u == z
        assert u * z == z
        assert u * u == u

    def test_int_vers_bin(self):
        assert int_vers_bin(11) == [1, 0, 1, 1]
        assert int_vers_bin(0) == [0]
        assert int_vers_bin(2, taille = 4) == [0, 0, 1, 0]

    def test_bin_vers_int(self):
        assert bin_vers_int(1, 0, 1, 1) == 11
        assert bin_vers_int() == bin_vers_int(0) == 0

    def test_int_log2(self):
        assert int_log2(3) == 2
        assert int_log2(4) == int_log2(5) == 3

    def test_int_vers_strbin(self):
        assert int_vers_strbin(11) == '1011'
        assert int_vers_strbin(0) == '0'
        assert int_vers_strbin(2, taille = 4) == '0010'

    def strbin_vers_int(self):
        assert strbin_vers_int('1011') == 11
        assert strbin_vers_int('0010') == 2

    def test_conjugue(self):
        assert F2(0).conjugue() == F2(0)
        assert F2(1).conjugue() == F2(1)


class TestF2Uplet(TestCase):
    def test_creation(self):
        assert F2.uplet(1) == F2Uplet(1)

    def test_eq(self):
        t1 = F2Uplet(un, un, zero)
        t2 = F2Uplet(1, 1, 0)
        assert t1 == t2

    def test_plus(self):
        t1 = F2Uplet(1, 0, 0)
        t2 = F2Uplet(1, 1, 0)
        t3 = F2Uplet(0, 1, 0)
        assert t1 + t2 == t3


class TestMatrice(TestCase):
    def test_zero(self):
        m = Matrice.zeros(2, 3)
        for k in range(2):
            for j in range(3):
                assert m[k, j] == zero

    def test_setitem(self):
        m = Matrice.zeros(2)
        assert m[0, 1] == zero
        m[0, 1] = un
        assert m[0, 1] == un
        m[0, 1] = 2
        assert m[0, 1] == Naturel(2)

    def test_tableau(self):
        m1 = Matrice([[un, zero], [un, zero]])
        m2 = Matrice([[1, zero], [1, 0]])
        assert m1[0, 0] == un
        assert m1[0, 1] == zero
        assert m1[1, 0] == un
        assert m1[1, 1] == zero
        assert m1 == m2

    def test_eq(self):
        m1 = Matrice([[1, 0], [0, 1]])
        m2 = Matrice([[1, 0], [0, 1]])
        assert m1 == m2
        assert m1 != Matrice.zeros(2)
        assert m1 != Matrice.zeros(2, 3)

    def test_fois(self):
        m1 = Matrice([[1, 2], [3, 4]])
        m2 = Matrice([[4, 5], [6, 7]])
        m3 = Matrice([[16, 19], [36, 43]])
        m4 = Matrice([[19, 28], [27, 40]])
        assert m1 * m2 == m3
        assert m2 * m1 ==  m4
        m5 = Matrice([[5], [6]])
        m6 = Matrice([[17], [39]])
        assert m1 * m5 == m6

    def test_fois_scalaire(self):
        m1 = Matrice([[2, 4], [6, 8]])
        m2 = Matrice([[1, 2], [3, 4]])
        assert Rationnel(1, 2) * m1 == m1 * Rationnel(1, 2) == m2
        assert m2 * Naturel(2) == m2 * 2 == m1

    def test_acces_rapide(self):
        l = Matrice([[1, 2]])
        c = Matrice([[1], [2]])
        assert l[1] == Naturel(2)
        assert c[1] == Naturel(2)
        l[1] = zero
        c[1] = un
        assert l[1] == zero
        assert c[1] == un

    def test_produit_tensoriel(self):
        m1 = Matrice([[1, 2], [3, 4]])
        m2 = Matrice([[5, 6], [7, 8]])
        m3 = Matrice([
            [5, 6, 10, 12],
            [7, 8, 14, 16],
            [15, 18, 20, 24],
            [21, 24, 28, 32]
        ])
        assert m1 @ m2 == m3
        m4 = sqrt(Rationnel(1, 2)) * Matrice([[1, 1], [1, -1]])
        m5 = Rationnel(1, 2) * Matrice([
            [1,  1,  1,  1],
            [1, -1,  1, -1],
            [1,  1, -1, -1],
            [1, -1, -1,  1]
        ])
        assert m4 @ m4 == m5

    def test_identite(self):
        m = Matrice.identite(3)
        for k in range(3):
            for j in range(3):
                if k == j:
                    assert m[k, j] == un
                else:
                    assert m[k, j] == zero

    def test_scalaire(self):
        assert Matrice.scalaire(un, 3) == Matrice.identite(3)
        assert Matrice.scalaire(-2, 3) == Matrice.identite(3) * (-2)

    def test_ligne(self):
        m = Matrice([[1, 2, 3]])
        assert Matrice.ligne(1, 2, 3) == m
        assert Matrice.ligne([1, 2, 3]) == m

    def test_colonne(self):
        m = Matrice([[1], [2], [3]])
        assert Matrice.colonne(1, 2, 3) == m
        assert Matrice.colonne([1, 2, 3]) == m


class TestVectPi(TestCase):
    def test_pi(self):
        assert pi == VectPi(1)
        assert pi == VectPi(un)

    def test_sous(self):
        assert VectPi(0).sous() == zero
        assert pi.sous() == pi
        assert VectPi(sqrt(2)) == VectPi(sqrt(2))

    def test_add(self):
        pi_sur_trois = VectPi(Rationnel(1, 3))
        pi_sur_quatre = VectPi(Rationnel(1, 4))
        pi_sur_six = VectPi(Rationnel(1, 12))
        assert pi - pi == zero
        assert pi + pi == VectPi(2)
        assert pi_sur_trois - pi_sur_quatre == pi_sur_six
        assert pi + zero == zero + pi == pi

    def test_mul(self):
        deux_pi = VectPi(2)
        assert zero * pi == pi * zero == zero
        assert un * pi == pi * un == pi
        assert pi * 2 == pi * Naturel(2) == deux_pi

    def test_div(self):
        assert pi / 2 == VectPi(Rationnel(1, 2))
        assert pi * 3 / 2 == VectPi(Rationnel(3, 2))

    def test_neg(self):
        assert (- VectPi(2)) == VectPi(-2)

    def test_mod2pi(self):
        assert (pi * 3).mod2pi() == (pi * -3).mod2pi() == pi
        assert (pi * 2).mod2pi() == (pi * -4).mod2pi() == zero


class TestExpi(TestCase):
    def test_eq(self):
        assert expi(-pi / 2) == expi(pi * 3 / 2)
        assert expi(-pi * 2 / 3) == expi(pi * 4 / 3)
        assert expi(pi / 2) == i

    def test_type(self):
        assert expi(pi) == (-un)
        assert expi(pi / 2) == i
        assert expi(pi / 3) == Expi(pi / 3)
        assert expi(pi / 4) == Expi(pi / 4)

    def test_exp0(self):
        assert expi(zero) == expi(0) == un
        assert Expi(zero) == Expi(0) != un

    def test_arg(self):
        e3i = expi(3)
        pi_sur_4 = VectPi(Rationnel(1, 4))
        eipi_sur_4 = expi(pi_sur_4)
        assert e3i.arg() == Naturel(3)
        assert eipi_sur_4.arg() == pi_sur_4

    def test_conjugue(self):
        assert expi(3).conjugue() == expi(-3)
        assert expi(pi * -3).conjugue() == expi(pi * 3)

    def test_abs(self): # le module
        z1 = Expi(1, module = 4)
        z2 = expi(3)
        assert abs(z1) == Naturel(4)
        assert abs(z2) == un

    def test_neg(self):
        assert -expi(pi / 3) == expi(pi * 4 / 3)

    def test_inverse(self):
        z1 = Expi(pi / 5, module=(un / 2))
        z2 = Expi(-pi / 5, module=2)
        assert z1.inverse() == z2
        assert z2.inverse() == z1
        assert un / expi(pi / 3) == expi(-pi / 3)

    def test_mul(self):
        z1 = expi(pi / 2)
        assert z1 * z1 == (-un)
        assert z1 * 3 == i * 3
        assert expi(pi / 3) * i == expi(pi * 5 / 6)
        z2 = expi(pi / 4) / 16
        z3 = i / 16
        assert z2 * z3 == expi(pi * 3 / 4) / 256
        assert Expi(pi / 4, module=sqrt(2)) == expi(pi / 4) * sqrt(2)

    def test_add(self):
        assert expi(pi / 3) + zero == zero + expi(pi / 3) == expi(pi / 3)
        assert expi(pi / 3) + expi(pi / 3) == expi(pi / 3) * 2
        assert expi(pi / 3) - expi(pi / 3) == zero
        assert -expi(pi / 3) + expi(pi / 3) == zero
        assert (expi(-pi / 4) * sqrt(2) + i) == un

    def test_pow(self):
        z1 = expi(pi / 6)
        z2 = expi(pi / 2)
        assert z1 ** 3 == z1 ** Naturel(3) == z2

    def test_sous(self):
        assert Expi(pi * 2).sous() == Expi(0).sous() == un
        assert Expi(pi).sous() == Expi(pi * 3).sous() == -un
        assert Expi(pi / 2).sous() == Expi(pi * (-3) / 2).sous() == i
        assert Expi(- pi / 2).sous() == Expi(pi * 3 / 2).sous() == -i

    def test_sur(self):
        assert Expi(pi / 4).sur(Complexe) == sqrt(un / 2) * (i + 1)


class TestSomme:
    def test_somme(self):
        assert somme(1, 2, 3) == Naturel(6)
        assert Somme(1, 2, 3).sous() == Naturel(6)
        assert Somme(1, 2, 3) != Naturel(6)

    def test_eq(self):
        assert Somme(1, 2, 3) == Somme(2, 3, 1)
        assert Somme(1, 2, 3) == Somme(6)
        assert Somme(1, 2, 3) != Naturel(6)
        assert Somme(1, sqrt(2)) == Somme(sqrt(2), 1)

    def test_sous(self):
        assert Somme(sqrt(2)).sous() == sqrt(2)
        assert Somme(sqrt(2), zero).sous() == sqrt(2)
        assert Somme(1, 2).sous() == Naturel(3)

    def test_plus_nombre(self):
        x = somme(1, sqrt(2))
        y = somme(Rationnel(3, 2), sqrt(2))
        assert x + Rationnel(1, 2) == y

    def test_plus_somme(self):
        x = somme(1, sqrt(2))
        y = somme(sqrt(3), 4)
        z = somme(sqrt(2), sqrt(3), 5)
        assert x + y == z

    def test_creation(self):
        assert sqrt(2) + 1 == Somme(sqrt(2), 1)
        assert sqrt(2) + 1 + 2 == Somme(sqrt(2), 3)

    def test_mul(self):
        assert sqrt(2) * (sqrt(2) + 1) == sqrt(2) + 2
        a = sqrt(2) + 1
        b = sqrt(2) - 1
        assert a * b == un
        assert a * a == sqrt(8) + 3

    def test_zeros(self):
        s = sqrt(2) + 1
        assert s - 1 == sqrt(2)

    def test_conjugue(self):
        s1 = i * sqrt(2) + 1
        s2 = -i * sqrt(2) + 1
        assert s1.conjugue() == s2
        assert s2.conjugue() == s1

    def test_abs(self):
        s1 = sqrt(2) + 1
        assert abs(s1) == s1
        assert abs(-s1) == s1
        s2 = Somme(expi(pi / 4), expi(-pi / 4))
        print(abs(s2), type(abs(s2)))
        assert abs(s2) == sqrt(2)


if __name__ == '__main__':
    main()
