#include "BSTree.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {
	int read_int(const std::string& prompt) {
		int val;
		while (true) {
			std::cout << prompt;
			if (std::cin >> val) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return val;
			}
			std::cout << "Ошибка: некорректный ввод! Пожалуйста, введите целое число.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::string read_string(const std::string& prompt) {
		std::cout << prompt;
		std::string s;
		while (std::getline(std::cin, s)) {
			if (!s.empty()) return s;
		}
		return s;
	}

	void print_menu() {
		std::cout << "\n================= МЕНЮ BSTree =================" << std::endl;
		std::cout << " 1. Добавить узел в дерево (push)" << std::endl;
		std::cout << " 2. Удалить узел из дерева (remove)" << std::endl;
		std::cout << " 3. Удалить все дерево (clear)" << std::endl;
		std::cout << " 4. Найти элемент в дереве (find)" << std::endl;
		std::cout << " 5. Вывести структуру дерева (operator<<)" << std::endl;
		std::cout << " 6. Прямой обход дерева (Pre-order)" << std::endl;
		std::cout << " 7. Симметричный обход дерева (In-order)" << std::endl;
		std::cout << " 8. Обратный обход дерева (Post-order)" << std::endl;
		std::cout << " 9. Слияние n деревьев (merge)" << std::endl;
		std::cout << "10. Сохранить дерево в файл (serialize)" << std::endl;
		std::cout << "11. Загрузить дерево из файла (deserialize)" << std::endl;
		std::cout << " 0. Выход из программы" << std::endl;
		std::cout << "===============================================" << std::endl;
	}
}

int main() {
	BSTree::BST tree;
	bool running = true;

	while (running) {
		print_menu();
		int choice = read_int("Выберите действие [0-11]: ");

		switch (choice) {
			case 1: {
				int key = read_int("Введите значение ключа для добавления: ");
				tree.push(key);
				std::cout << "Узел с ключом " << key << " добавлен.\n";
				break;
			}
			case 2: {
				if (tree.empty()) {
					std::cout << "Дерево пусто.\n";
					break;
				}
				int key = read_int("Введите значение ключа для удаления: ");
				if (!tree.find(key)) {
					std::cout << "Ключ " << key << " не найден в дереве.\n";
				} else {
					tree.remove(key);
					std::cout << "Узел с ключом " << key << " удалён.\n";
				}
				break;
			}
			case 3: {
				tree.clear();
				std::cout << "Дерево полностью очищено.\n";
				break;
			}
			case 4: {
				if (tree.empty()) {
					std::cout << "Дерево пусто.\n";
					break;
				}
				int key = read_int("Введите значение ключа для поиска: ");
				if (tree.find(key)) {
					std::cout << "Элемент с ключом " << key << " НАЙДЕН в дереве.\n";
				} else {
					std::cout << "Элемент с ключом " << key << " НЕ НАЙДЕН в дереве.\n";
				}
				break;
			}
			case 5: {
				if (tree.empty()) {
					std::cout << "Дерево пусто.\n";
				} else {
					std::cout << "Структура дерева (ключ: левый правый):\n" << tree;
				}
				break;
			}
			case 6: {
				if (tree.empty()) {
					std::cout << "Дерево пусто.\n";
				} else {
					std::cout << "Прямой обход (Pre-order): ";
					tree.pre_order(std::cout);
					std::cout << "\n";
				}
				break;
			}
			case 7: {
				if (tree.empty()) {
					std::cout << "Дерево пусто.\n";
				} else {
					std::cout << "Симметричный обход (In-order): ";
					tree.in_order(std::cout);
					std::cout << "\n";
				}
				break;
			}
			case 8: {
				if (tree.empty()) {
					std::cout << "Дерево пусто.\n";
				} else {
					std::cout << "Обратный обход (Post-order): ";
					tree.post_order(std::cout);
					std::cout << "\n";
				}
				break;
			}
			case 9: {
				int n = read_int("Введите количество деревьев для слияния (n >= 1): ");
				if (n <= 0) {
					std::cout << "Количество деревьев должно быть не менее 1.\n";
					break;
				}
				std::vector<BSTree::BST> trees;
				trees.reserve(n);

				for (int i = 0; i < n; ++i) {
					std::cout << "\n--- Заполнение дерева #" << (i + 1) << " ---\n";
					int count = read_int("Количество элементов в дереве #" + std::to_string(i + 1) + ": ");
					BSTree::BST t;
					for (int j = 0; j < count; ++j) {
						int k = read_int("  Элемент [" + std::to_string(j + 1) + "]: ");
						t.push(k);
					}
					trees.push_back(std::move(t));
				}

				BSTree::BST merged = BSTree::BST::merge(trees.data(), trees.size());
				std::cout << "\nРезультат слияния " << n << " деревьев:\n" << merged;

				int replace = read_int("\nСделать объединённое дерево текущим рабочим деревом? (1 - да, 0 - нет): ");
				if (replace == 1) {
					tree = std::move(merged);
					std::cout << "Текущее рабочее дерево обновлено.\n";
				}
				break;
			}
			case 10: {
				std::string filename = read_string("Введите имя файла для сохранения: ");
				tree.serialize(filename);
				std::cout << "Дерево сохранено в файл '" << filename << "'.\n";
				break;
			}
			case 11: {
				std::string filename = read_string("Введите имя файла для загрузки: ");
				tree.deserialize(filename);
				std::cout << "Дерево загружено из файла '" << filename << "'.\n";
				break;
			}
			case 0: {
				std::cout << "Выход из программы...\n";
				running = false;
				break;
			}
			default:
				std::cout << "Неверный пункт меню! Выберите число от 0 до 11.\n";
				break;
		}
	}

	return 0;
}
