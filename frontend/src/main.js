import Vue from 'vue';
import App from './App.vue';
import router from './router';
import store from './store';
import axios from 'axios';
import vuetify from './plugins/vuetify';

Vue.config.productionTip = false;

axios.defaults.baseURL = 'http://localhost:34568/';

Vue.filter('formatCardNum', cardNum => {
  let formattedCardNum = '';

  for (let i = 4; i <= 16; i += 4) {
    formattedCardNum += `${cardNum.slice(i - 4, i)} \u2014 `;
  }

  return formattedCardNum.slice(0, formattedCardNum.length - 2);
});

Vue.filter('formatCardNumWithMask', cardNum => {
  return `${cardNum.slice(0, 4)} \u2014 .... \u2014 .... \u2014 ${cardNum.slice(
    12,
    16
  )}`;
});

new Vue({
  router,
  store,
  vuetify,
  render: h => h(App),
}).$mount('#app');
