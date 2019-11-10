import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    user_cards: [
      {
        card_name: 'Sample 1',
        card_number: '1232123112341231',
        card_balance: 1234.12,
        card_expiration: '22-12-2019',
      },
      {
        card_number: '1232123457141231',
        card_balance: 1234.12,
        card_expiration: '22-03-2021',
      },
      {
        card_name: 'Hello World',
        card_number: '1232112322341231',
        card_balance: 1234.12,
        card_expiration: '22-03-2022',
      },
    ],
    user_transactions: [
      {
        sender: 'John Doe',
        sender_card: '1234123412341234',
        receiver: 'Jane Doe',
        receiver_card: '1232112322341231',
        description: 'Lorem ipsum',
        sum: 1234.23,
        date: '12-08-2019',
        time: '12:12',
      },
      {
        sender: 'John Doe',
        sender_card: '1234123412341234',
        receiver: 'Jane Doe',
        receiver_card: '1232112322341231',
        description: 'Lorem ipsum',
        sum: 200.0,
        date: '12-08-2019',
        time: '14:12',
      },
    ],
    user_templates: [
      {
        receiver: 'Jane Doe',
        receiver_card: '1232112322341231',
        description: 'Lorem ipsum',
        sum: 200.0,
      },
    ],
    user_deposits: [
      {
        card_number: '1234123412341234',
        deposit_balance: 1231,
        deposit_start: '12-02-2020',
        deposit_expiration: '12-09-2022',
      },
    ],
    user_data: [],
    user_authorized: false,
    performing_request: false,
  },
  mutations: {
    ADD_CARD(state, card) {
      state.user_cards.push(card);
    },
    SET_CARDS(state, cards) {
      state.user_cards = cards;
    },
    ADD_TEMPLATE(state, template) {
      state.user_templates.push(template);
    },
    SET_TEMPLATES(state, templates) {
      state.user_templates = templates;
    },
    PERFORM_TRANSACTION(state, transaction) {
      state.user_transactions.push(transaction);
    },
    SET_TRANSACTIONS(state, transactions) {
      state.user_transactions = transactions;
    },
    CREATE_DEPOSIT(state, deposit) {
      state.user_deposits.push(deposit);
    },
    SET_DEPOSITS(state, deposits) {
      state.user_deposits = deposits;
    },
    SET_USER(state, userData) {
      state.user_data = userData;
    },
    AUTHORIZE(state, payload) {
      state.user_authorized = payload;
    },
    SET_PASSWORD(state, payload) {
      state.user_data.password = payload;
    },
  },
  actions: {
    addCard(context, payload) {
      // TODO: perform POST request to the server
      context.commit('ADD_CARD', payload);
    },
    addTemplate(context, payload) {
      // TODO: perform POST request to the server
      context.commit('ADD_TEMPLATE', payload);
    },
    performTransaction(context, payload) {
      // TODO: perform POST request to the server
      context.commit('PERFORM_TRANSACTION', payload);
    },
    createDeposit(context) {
      // TODO: perform POST request to the server
      context.commit('CREATE_DEPOSIT', 'DUMMY DATA');
    },
    changePassword(context, payload) {
      // TODO: perform POST request to the server
      context.commit('SET_PASSWORD', payload);
    },
    registerUser(context, payload) {
      // TODO: perform POST request to the server
      context.commit('SET_USER', payload);
    },
    authorizeUser() {
      // TODO: perform POST request to the server
    },
    fetchUserCards() {
      // TODO: perform GET request to the server
    },
    fetchUserTransactions() {
      // TODO: perform GET request to the server
    },
    fetchUserTemplates() {
      // TODO: perform GET request to the server
    },
    fetchUserDeposits() {
      // TODO: perform GET request to the server
    },
  },
  getters: {
    getCards(state) {
      return state.user_cards;
    },
    getTemplates(state) {
      return state.user_templates;
    },
    getTransactions(state) {
      return state.user_transactions;
    },
    getDeposits(state) {
      return state.user_deposits;
    },
    userIsAuthorized(state) {
      return state.user_authorized;
    },
  },
});
