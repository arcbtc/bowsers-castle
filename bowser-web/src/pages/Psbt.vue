<template>
  <q-page>
    <div class="row q-col-gutter-md justify-center">
      <div class="col-12 col-md-10 col-lg-10 q-gutter-y-md">
        <h5 class="q-pt-lg q-mb-xs">
          Build PSBT
        </h5>
        <q-card class="q-mt-lg">
          <q-card-section>
            <q-form @submit="findUtxos" class="q-gutter-md">
              <div class="row">
                <div class="col-9">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="xPub"
                    label="xpub/zpub"
                  ></q-input>
                </div>
                <div class="col-3">
                  <q-btn-dropdown :label="network">
                    <q-list>
                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('bitcoin')"
                      >
                        <q-item-section>
                          <q-item-label>Bitcoin</q-item-label>
                        </q-item-section>
                      </q-item>

                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('testnet')"
                      >
                        <q-item-section>
                          <q-item-label>Testnet</q-item-label>
                        </q-item-section>
                      </q-item>

                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('regtest')"
                      >
                        <q-item-section>
                          <q-item-label>Regtest</q-item-label>
                        </q-item-section>
                      </q-item>
                    </q-list>
                  </q-btn-dropdown>
                </div>
              </div>
              <div class="row">
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="derivationRoot"
                    label="derivation root (eg: m/44'/0'/0'/0)"
                  ></q-input>
                </div>
                <div class="col-1"></div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="derivationStartIndex"
                    label="derivation start index"
                  ></q-input>
                </div>
                <div class="col-1"></div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="derivationSize"
                    label="size"
                  ></q-input>
                </div>
                <div class="col-2"></div>
              </div>

              <q-btn
                unelevated
                color="primary"
                :disable="xPub == ''"
                type="submit"
                >Find UTXOs</q-btn
              >
            </q-form>
          </q-card-section>
        </q-card>

        <q-card class="q-mt-lg">
          <q-card-section>
            <div class="row">
              <div class="col-6">
                <h6 class="text-subtitle1 q-mt-none q-mb-sm">
                  UTXO List
                </h6>
              </div>
              <div class="col-6">
                <div align="right">
                  <q-btn
                    @click="toggleEmptyAddresses"
                    unelevated
                    color="secondary"
                    >{{ showEmptyAddresses ? "Hide" : "Show" }} Empty
                    Addresses</q-btn
                  >
                </div>
              </div>
            </div>
          </q-card-section>
          <q-card-section>
            <q-table
              :data="tableData"
              :columns="columns"
              row-key="id"
              :pagination="pagination"
              dark
              color="amber"
            />
          </q-card-section>
        </q-card>

        <q-card class="q-mt-lg">
          <q-card-section>
            <q-form @submit="buildPsbt" class="q-gutter-md">
              <div class="row">
                <div class="col-9">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="destinationAddress"
                    label="destination address"
                  ></q-input>
                </div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="sentAmount"
                    type="number"
                    label="amount (sats)"
                  ></q-input>
                </div>
              </div>
              <div class="row">
                <div class="col-9">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="changeAddress"
                    label="change address"
                  ></q-input>
                </div>

                <div class="col-3">
                  <q-btn-dropdown :label="`${feeMode} (${feeValue})`">
                    <q-list>
                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectFee('fastestFee')"
                      >
                        <q-item-section>
                          <q-item-label
                            >Fastest Fee ({{
                              fees.fastestFee || ""
                            }})</q-item-label
                          >
                        </q-item-section>
                      </q-item>

                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectFee('halfHourFee')"
                      >
                        <q-item-section>
                          <q-item-label
                            >Half Hour Fee ({{
                              fees.halfHourFee || ""
                            }})</q-item-label
                          >
                        </q-item-section>
                      </q-item>

                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectFee('hourFee')"
                      >
                        <q-item-section>
                          <q-item-label
                            >Hour Fee ({{ fees.hourFee || "" }})</q-item-label
                          >
                        </q-item-section>
                      </q-item>
                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectFee('minimumFee')"
                      >
                        <q-item-section>
                          <q-item-label
                            >Minimum Fee ({{
                              fees.minimumFee || ""
                            }})</q-item-label
                          >
                        </q-item-section>
                      </q-item>
                    </q-list>
                  </q-btn-dropdown>
                </div>
              </div>

              <q-btn unelevated color="primary" type="submit">Buld PSBT</q-btn>
              <div class="row">
                <div class="col-12">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    autogrow
                    v-model="base64Psbt"
                    label="base64 PSBT"
                  ></q-input>
                </div>
              </div>
            </q-form>
          </q-card-section>
        </q-card>
      </div>
    </div>
  </q-page>
</template>

<script>
const bjs = require("bitcoinjs-lib");
const coinselect = require("coinselect");

const utxoSvc = require("../services/utxo.service")("mempool");
const feeSvc = require("../services/fee.service")("mempool");
const txSvc = require("../services/tx.service")("mempool");

export default {
  data() {
    return {
      xPub: "",
      derivationRoot: "0",
      derivationStartIndex: 0,
      derivationSize: 10,
      network: "testnet",
      destinationAddress: "",
      sentAmount: 0,
      changeAddress: "",
      fees: {},
      feeMode: "fastestFee",
      feeValue: "",

      tableData: [],
      utxoList: [],
      addressList: [],
      base64Psbt: "",

      columns: [
        {
          name: "address",
          required: true,
          label: "Address",
          align: "left",
          field: row => row.address,
          format: val => `${val || ""}`,
          sortable: true
        },

        {
          name: "amount",
          align: "center",
          label: "Amount",
          field: "value",
          sortable: true
        },
        {
          name: "vout",
          align: "center",
          label: "VOut",
          field: "vout",
          sortable: true
        },
        {
          name: "txid",
          required: false,
          label: "Transaction ID",
          align: "left",
          field: row => row.txid,
          format: val => `${val || ""}`,
          sortable: true
        }
      ],
      pagination: {
        rowsPerPage: 30
      },
      showEmptyAddresses: false
    };
  },
  methods: {
    async findUtxos() {
      const dismissNotification = this.showMesage("Searching UTXOs");
      this.utxoList = [];
      this.tableData = [];
      try {
        // no need to 'await'
        this.updateFees();

        const allUtxos = await this.fetchUtxoListForMasterPubKey(this.xPub);
        const tableData = this.utxoListToTableData(allUtxos);

        this.utxoList = tableData.concat();
        this.tableData = this.showEmptyAddresses
          ? tableData
          : tableData.filter(d => d.txid);
        this.changeAddress = this.findChangeAddress();
      } catch (err) {
        this.showError(err);
      } finally {
        dismissNotification();
      }
    },
    async updateFees() {
      try {
        this.fees = await feeSvc.getRecommendedFees();
        this.feeValue = this.fees[this.feeMode];
      } catch (err) {
        this.showError(err);
      }
    },
    async buildPsbt() {
      const dismissNotification = this.showMesage("Building PSBT");
      try {
        if (!this.destinationAddress) {
          throw new Error("Destination address is missing");
        }
        if (!this.changeAddress) {
          throw new Error("Change address is missing");
        }
        const x = this.utxoList.filter(d => d.txid);
        const utxoList = await this.enrichUtxoList(x);
        const destination = {
          address: this.destinationAddress,
          value: +this.sentAmount
        };
        const txData = coinselect(utxoList, [destination], this.feeValue);

        if (!txData.inputs || !txData.inputs.length) {
          throw new Error(
            "Cannot select coins using the provided UTXO set and coin selection algorithm!"
          );
        }
        const psbt = this.txDataToPsbt(txData, this.changeAddress);
        this.base64Psbt = psbt.toBase64();
      } catch (err) {
        this.showError(err);
      } finally {
        dismissNotification();
      }
    },
    async enrichUtxoList(utxoList) {
      const enrichedUtxoList = [];
      for (const utxo of utxoList) {
        const tx = await txSvc.getTx(utxo.txid);
        const output = tx.vout[utxo.vout];
        enrichedUtxoList.push({
          txid: utxo.txid,
          vout: utxo.vout,
          value: utxo.value,
          witnessUtxo: {
            script: Buffer.from(output.scriptpubkey, "hex"),
            value: utxo.value
          }
        });

        // TODO: check for non-witness output (requires TX Hex)
      }
      return enrichedUtxoList;
    },
    async fetchUtxoListForMasterPubKey(masterPubKey) {
      const xPub = masterPubKey.toLowerCase().startsWith("zpub")
        ? this.zpubToXpub(masterPubKey)
        : masterPubKey;
      const network = bjs.networks[this.network];
      const hdNode = bjs.bip32.fromBase58(xPub, network);

      this.addressList = this.deriveAddresses(hdNode, {
        rootPath: this.derivationRoot,
        start: this.derivationStartIndex,
        size: this.derivationSize,
        network
      });

      const utxoPromisses = this.addressList.map(address => {
        return utxoSvc.getUtxosForAddress(address);
      });
      return Promise.all(utxoPromisses);
    },
    utxoListToTableData(allUtxos) {
      const data = [];
      allUtxos.forEach((utxos, index) => {
        if (!utxos.length) {
          data.push({
            id: data.length,
            address: this.addressList[index]
          });
          return;
        }
        utxos.forEach((utxo, i) => {
          data.push({
            id: data.length,
            address: i === 0 ? this.addressList[index] : "",
            txid: utxo.txid,
            value: utxo.value,
            vout: utxo.vout
          });
        });
      });
      return data;
    },
    txDataToPsbt(txData, changeAddress) {
      const psbt = new bjs.Psbt({
        network: bjs.networks[this.network]
      });

      txData.inputs.forEach(input => {
        psbt.addInput({
          hash: input.txid,
          index: input.vout,
          witnessUtxo: input.witnessUtxo,
          value: input.value
        });
      });

      txData.outputs.forEach(out => {
        if (!out.address) {
          out.address = changeAddress;
        }
        psbt.addOutput(out);
      });

      return psbt;
    },
    findChangeAddress() {
      const lastUtxo = this.utxoList[this.utxoList.length - 1];
      if (lastUtxo && lastUtxo.txid) {
        return "";
      }
      for (let i = this.utxoList.length - 2; i >= 0; i--) {
        if (this.utxoList[i] && this.utxoList[i].txid) {
          return this.utxoList[i + 1].address;
        }
      }
      return "";
      // todo: if empty not found
    },
    selectNetwork(network) {
      this.network = network;
    },
    selectFee(feeMode) {
      this.feeMode = feeMode;
      this.feeValue = this.fees[this.feeMode];
    },
    toggleEmptyAddresses() {
      this.showEmptyAddresses = !this.showEmptyAddresses;
      this.tableData = this.showEmptyAddresses
        ? this.utxoList
        : this.utxoList.filter(d => d.txid);
    },
    deriveAddresses(node, op = {}) {
      const start = op.start || 0;
      const size = op.size || 10;
      const rootPath = op.rootPath || "m/84'/0'/0'/0";
      const network = op.network || bjs.networks.testnet;

      const addresses = [];
      for (let i = start; i < start + size; i++) {
        const derivationPath = `${rootPath}/${i}`;
        const publicKey = node.derivePath(derivationPath).publicKey;
        const payment = bjs.payments.p2wpkh({
          pubkey: publicKey,
          network
        });
        addresses.push(payment.address);
      }
      return addresses;
    },
    zpubToXpub(zpub) {
      let data = b58.decode(zpub);
      data = data.slice(4);
      data = Buffer.concat([Buffer.from("0488b21e", "hex"), data]);
      return b58.encode(data);
    },
    showError(err) {
      console.error(err);
      this.$q.notify({
        icon: "error",
        type: "warning",
        message: err.message || err
      });
    },
    showMesage(message = "...") {
      return this.$q.notify({
        timeout: 0,
        spinner: true,
        message
      });
    }
  },
  async mounted() {
    this.updateFees();
  }
};
</script>
