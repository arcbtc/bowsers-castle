const axios = require('axios');

let HOST = ''


async function getTx(txId) {
    if (!txId) {
        throw new Error('Transaction ID is missing!');
    }
    const response = await axios.get(`${HOST}/api/tx/${txId}`);
    if (response.status !== 200) {
        throw new Error(`Cannot fetch Transaction for ID ${txId}`);
    }
    return response.data;
}

async function getTxHex(txId) {
    if (!txId) {
        throw new Error('Transaction ID is missing!');
    }
    const response = await axios.get(`${HOST}/api/tx/${txId}/hex`);
    if (response.status !== 200) {
        throw new Error(`Cannot fetch Transaction for ID ${txId}`);
    }
    return response.data;
}

function init(host) {
    if (!host) {
        throw new Error('Please provide the host value!');
    }
    HOST = host;
    return {
        getTxHex,
        getTx
    }
}

module.exports = init;