import Vue from 'vue';
import VueRouter from 'vue-router';
import Hub from '../views/Hub.vue';

import Banking from '../views/Banking/Banking.vue';
import BankingHome from '../views/Banking/BankingHome.vue';
import BankingCards from '../views/Banking/Cards/BankingCards.vue';
import BankingTransactions from '../views/Banking/Transactions/BankingTransactions.vue';
import BankingTemplates from '../views/Banking/Templates/BankingTemplates.vue';
import BankingDeposits from '../views/Banking/Deposits/BankingDeposits.vue';

import Terminal from '../views/Terminal/Terminal.vue';
import TerminalHome from '../views/Terminal/TerminalHome.vue';
import TerminalReplenish from '../views/Terminal/TerminalReplenish.vue';

Vue.use(VueRouter);

const routes = [
  {
    path: '/',
    name: 'home',
    component: Hub,
  },
  {
    path: '/terminal',
    name: 'terminal',
    component: Terminal,
    children: [
      {
        path: '',
        component: TerminalHome,
      },
      {
        path: 'replenish',
        component: TerminalReplenish,
      },
    ],
  },
  {
    path: '/berking',
    name: 'banking',
    component: Banking,
    children: [
      {
        path: '',
        component: BankingHome,
      },
      {
        path: 'cards',
        component: BankingCards,
      },
      {
        path: 'transactions',
        component: BankingTransactions,
      },
      {
        path: 'templates',
        component: BankingTemplates,
      },
      {
        path: 'deposits',
        component: BankingDeposits,
      },
    ],
  },
  // {
  //   path: '/about',
  //   name: 'about',
  //   // route level code-splitting
  //   // this generates a separate chunk (about.[hash].js) for this route
  //   // which is lazy-loaded when the route is visited.
  //   component: () => import(/* webpackChunkName: "about" */ '../views/About.vue'),
  // },
];

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes,
});

export default router;