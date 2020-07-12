#!/bin/bash
# copy web3 keys to home directory
cp -rf .web3  ~/
# run aleth with given configuration
aleth  --test --config $(pwd)/config.json --password 123456 --db-path $(pwd)/Ethereum --data-dir $(pwd)/Ethereum -m on  -t 6  -a   00eed452f13e237af8089e372c588382990a2df0 --no-discovery --pin --unsafe-transactions

