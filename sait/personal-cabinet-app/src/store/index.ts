import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    user: null,
    audioFiles: {}
  },
  mutations: {
    setUser(state, user) {
      state.user = user;
    },
    addAudioFile(state, { userId, audioFile }) {
      if (!state.audioFiles[userId]) {
        state.audioFiles[userId] = [];
      }
      state.audioFiles[userId].push(audioFile);
    }
  },
  actions: {
    uploadAudioFile({ commit }, { userId, audioFile }) {
      // Здесь можно добавить логику для загрузки аудиофайла на сервер
      commit('addAudioFile', { userId, audioFile });
    },
    setUser({ commit }, user) {
      commit('setUser', user);
    }
  },
  getters: {
    getUser(state) {
      return state.user;
    },
    getAudioFilesByUser(state) {
      return (userId) => state.audioFiles[userId] || [];
    }
  }
});