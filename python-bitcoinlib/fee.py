#Calculate transaction's fee

from bitcoin.rpc import RawProxy

p = RawProxy()

#Enter transaction's id

txid = input('Enter transaction id\n')

#Retrieve raw transaction

raw_tx = p.getrawtransaction(txid)

#Decode transaction

decoded_tx = p.decoderawtransaction(raw_tx)

total_out = 0

for output in decoded_tx['vout']:
    total_out += output['value']

total_in = 0

for input in decoded_tx['vin']:
    a = p.decoderawtransaction(p.getrawtransaction(input['txid']))
    for output in a['vout']:
        total_in += output['value']

total = total_in - total_out

print('Total input ' + str(total_in))
print('Total output ' + str(total_out))
print('Fee ' + str(total))

