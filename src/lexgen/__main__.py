
from argparse import ArgumentParser, FileType

from genlexer import generate
from parsezlex import parse_zlex


parser = ArgumentParser('zlexgen', description='Oh god a lexer generator...')
parser.add_argument('--output', '-o', type=FileType('w'))
parser.add_argument('inputs', nargs='*', type=FileType('r'))

args = parser.parse_args()
lexdesc = parse_zlex(*args.inputs)
generate(lexdesc, args.output)
