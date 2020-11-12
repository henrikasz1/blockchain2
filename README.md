# blockchain2

:hash: It is a simple program, which represents a simplified work of blockchain :hash:

**Aspects to be included in program:**

**V 0.1: **

* Generate 1000 users that must have name, publi_key and balance attributes
* Generate 10000 transactions that must have transaction id, sender id, reciepient id and the amount of money attributes
* Randomly choose 100 transactions which will be inserted into a new block
* Mine a new block and find a hash which will comply difficulty targer
* Delete transactions from the pool that has been added to a new block
* Update users balances
* Insert a mined block into a blockchain

**V0.2: **

* Implement Merkle tree in block hashing
* Implement balance and hash verification
* Improve mining process

**How the program works:**

* Generates 1000 users with the required aspects :heavy_check_mark:
* Generates 10000 transactions with the required aspects :heavy_check_mark:
* Verifies transactions by its balance and hash :heavy_check_mark:
* Randomly selects transactions which will be inserted into a new block :heavy_check_mark:
* Creates five new blocks with randomly chosen transactions :hevy_check_mark:
* Tries to mine one of those five blocks and inserts the mined block into a block chain :heavy_check_mark:
* Updates users balances
* Repeats the process until the transaction pool will be empty :heavy_check_mark:
