<template>
  <q-page>
    <div class="row q-col-gutter-md justify-center">
      <div class="col-12 col-md-7 col-lg-6 q-gutter-y-md">
        <q-card class="q-mt-lg">
          <q-card-section>
            <q-form @submit="sendFunds" class="q-gutter-md">
              <div class="row">
                <div class="col-9">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="btcAddress"
                    label="Bitcoin address"
                  ></q-input>
                </div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="btcAmount"
                    label="Amount"
                  ></q-input>
                </div>
              </div>

              <q-btn
                unelevated
                color="primary"
                :disable="btcAddress == '' || btcAmount < 0.0001"
                type="submit"
                >Send bitcoin</q-btn
              >
            </q-form>
          </q-card-section>
        </q-card>

        <q-card class="q-mt-lg">
          <q-card-section>
            <h6 class="text-subtitle1 q-mt-none q-mb-sm">
              Transactions:
            </h6>
          </q-card-section>
          <q-card-section>
            <q-table
            
              :data="data"
              :columns="columns"
              row-key="name"
              dark
              color="amber"
            />
          </q-card-section>
        </q-card>
      </div>
      <div class="col-12 col-md-3 q-gutter-y-md">
        <q-card>
          <q-card-section>
            <h6 class="text-subtitle1 q-mt-none q-mb-sm">
              Bowser uses <a target="_blank" href="https://mempool.space">mempool.space</a> api for transaction data,<br/>you can also use use your own mempool.space
            </h6>
          </q-card-section>
          <q-card-section class="q-px-auto">
            <q-btn unelevated color="primary" icon="edit">
              <div class="cursor-pointer">
                <q-tooltip> Point to another Mempool </q-tooltip>
                {{ this.mempool.endpoint }}
                <q-popup-edit v-model="mempool.endpoint">
                  <q-input color="accent" v-model="mempool.endpoint"> </q-input>
                  <center>
                    <q-btn flat dense @click="updateMempool()" v-close-popup
                      >set</q-btn
                    >
                    <q-btn flat dense v-close-popup>cancel</q-btn>
                  </center>
                </q-popup-edit>
              </div>
            </q-btn>
          </q-card-section>
     
        </q-card>
      </div>
    </div>
  </q-page>
</template>

<script>
export default {
  data() {
    return {
      mempool: {
        endpoint: "https://mempool.space"
      },
      btcAddress: "",
      btcAmount: 0,
      columns: [
        {
          name: "desc",
          required: true,
          label: "Transaction id",
          align: "left",
          field: row => row.name,
          format: val => `${val}`,
          sortable: true
        },
        {
          name: "amount",
          align: "center",
          label: "Amount",
          field: "amount",
          sortable: true
        },
        { name: "date", label: "Date", field: "date", sortable: true }
      ],
      data: [
        {
          name: "12c6DSiU4Rq3P4ZxziKxzrL5LmMBrzjrJX",
          amount: 159,
          date: "10.10.21"
        },
      ]
    };
  },
  methods: {
    async sendFunds() {},
    async updateMempool() {
      self = this;
      self.mempool.endpoint = self.mempool;
    },
    async getTransactions() {
      self = this;
      self.mempool.endpoint = self.mempool;
    }
  }
};
</script>
