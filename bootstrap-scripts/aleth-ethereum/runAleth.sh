#!/bin/bash
# copy web3 keys to home directory
rm -rf ./Ethereum
mkdir -p ./Ethereum
cp -rf keystore ./Ethereum
cp -rf .web3  ~/
# run aleth with given configuration
aleth --config $(pwd)/config.json --master "" --password 123456 --db-path $(pwd)/Ethereum --data-dir $(pwd)/Ethereum -m on -a   00eed452f13e237af8089e372c588382990a2df0 --no-discovery --pin --unsafe-transactions --test

