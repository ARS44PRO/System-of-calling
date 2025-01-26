<template>
  <div class="user-dashboard">
    <h1>Личный кабинет пользователя</h1>
    <div class="user-info">
      <h2>Информация о пользователе</h2>
      <p>Имя: {{ user.name }}</p>
      <p>Email: {{ user.email }}</p>
    </div>
    <div class="audio-files">
      <h2>Загруженные аудиофайлы</h2>
      <ul>
        <li v-for="audio in audioFiles" :key="audio.id">
          {{ audio.name }}
        </li>
      </ul>
    </div>
    <AudioUploader @upload="fetchAudioFiles" />
  </div>
</template>

<script>
import { mapState } from 'vuex';
import AudioUploader from '@/components/AudioUploader.vue';

export default {
  components: {
    AudioUploader,
  },
  computed: {
    ...mapState(['user', 'audioFiles']),
  },
  methods: {
    fetchAudioFiles() {
      // Логика для получения загруженных аудиофайлов
    },
  },
};
</script>

<style scoped>
.user-dashboard {
  padding: 20px;
}
.user-info {
  margin-bottom: 20px;
}
.audio-files {
  margin-top: 20px;
}
</style>