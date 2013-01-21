# Dado uma expressao regular eh gerado uma quantidade
# N de strings que pertencem a essa expressao regular
# Instalar o seguinte modulo python exrex
# https://github.com/asciimoo/exrex
# Utilizacao:
# python generate_strings.py '<regex>'
# as strings sao salvas no arquivo strings no mesmo diretorio

import sys
import os
import exrex

regex = sys.argv[1]

file = open('strings', 'wr')

#modificar o range para quantida de strings que quiseremos
for i in range(5000):
	palavrao = exrex.getone(regex)
	if len(palavrao) <=50:
		file.write(palavrao+ " ")
