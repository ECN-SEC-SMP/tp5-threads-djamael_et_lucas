# === Exécution rapide ===
#=> mingw32-make run ou make run


# === Configuration ===
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJ = main.o
TARGET = TP5exe

# === Règle par défaut ===
all: $(TARGET)

# === Liaison ===
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

# === Compilation des .cpp en .o ===
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# === Nettoyage ===
clean:
	del /Q $(OBJ) $(TARGET).exe 2>nul || true


# === Exécution rapide ===
run: all
	@echo Activation de l'encodage UTF-8 pour le terminal...
	@chcp 65001 >nul
	@echo Lancement de l'exécutable
	.\$(TARGET).exe
