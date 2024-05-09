int main() {
    FILE *file = fopen("music.mp3", "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening music file\n");
        return 1;
    }

    play_music(file);
    fclose(file);
    return 0;
}
