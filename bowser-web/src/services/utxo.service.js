const axios = require('axios');

let HOST = ''

async function getUtxosForAddress(addr) {
    if (!addr) {
        throw new Error('Address is missing!');
    }
    const response = await axios.get(`${HOST}/api/address/${addr}/utxo`);
    if (response.status !== 200) {
        throw new Error(`Cannot fetch UTXOs for address ${addr}`);
    }
    return response.data;
}

async function getUtxosForAddressList(addressList = []) {
    let utxoList = []
    for (addr of addressList) {
        const utxos = await getUtxosForAddress(addr);
        utxoList = utxoList.concat(utxos);
    }
    utxoList.forEach(utxo => (delete utxo.status));
    return utxoList;
}

function init(host) {
    if (!host) {
        throw new Error('Please provide the host value!');
    }
    HOST = host;
    return {
        getUtxosForAddress,
        getUtxosForAddressList
    }
}

module.exports = init;