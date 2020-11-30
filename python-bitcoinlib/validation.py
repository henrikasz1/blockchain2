#Validate hash

from bitcoin.rpc import RawProxy
import hashlib

p = RawProxy()

# https://stackoverflow.com/questions/46109815/convert-string-from-big-endian-to-little-endian-or-vice-versa-in-python
# Convert to little-endian
# :02x converts int into string of hex
def convert(input):
    a = bytearray.fromhex(input)
    a.reverse()
    return ''.join(format(x, '02x') for x in a)

def convert_int(input):
    return '{:02x}'.format(input)

block_id = input('Enter block id \n')

header = p.getblockheader(block_id)

version = convert(header['versionHex'])
hashPrevBlock = convert(header['previousblockhash'])
hashMerkleRoot = convert(header['merkleroot'])
time = convert(convert_int(header['time']))
bits = convert(header['bits'])
nonce = convert(convert_int(header['nonce']))

h = version + hashPrevBlock + hashMerkleRoot + time + bits + nonce

header_bin = h.decode('hex')
hash = hashlib.sha256(hashlib.sha256(header_bin).digest()).digest()
hash.encode('hex_codec')


if (header['hash'] == hash[::-1].encode('hex_codec')):
    print('Valid')
else:
    Print('Not valid')