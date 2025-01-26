<template>
  <div class="audio-uploader">
    <h2>Загрузить аудиофайл</h2>
    <input type="file" @change="onFileChange" accept="audio/*" />
    <button @click="uploadAudio" :disabled="!selectedFile">Загрузить</button>
    <p v-if="uploadStatus">{{ uploadStatus }}</p>
  </div>
</template>

<script>
export default {
  data() {
    return {
      selectedFile: null,
      uploadStatus: ''
    };
  },
  methods: {
    onFileChange(event) {
      this.selectedFile = event.target.files[0];
    },
    async uploadAudio() {
      if (!this.selectedFile) return;

      const formData = new FormData();
      formData.append('audio', this.selectedFile);

      try {
        const userId = this.$store.state.user.id; // Получаем ID пользователя из хранилища
        const response = await fetch(`/api/audio/${userId}`, {
          method: 'POST',
          body: formData
        });

        if (response.ok) {
          this.uploadStatus = 'Аудиофайл успешно загружен!';
          this.selectedFile = null; // Сбросить выбранный файл
        } else {
          this.uploadStatus = 'Ошибка при загрузке аудиофайла.';
        }
      } catch (error) {
        this.uploadStatus = 'Ошибка сети.';
      }
    }
  }
};
</script>

<style scoped>
.audio-uploader {
  margin: 20px;
}
</style>