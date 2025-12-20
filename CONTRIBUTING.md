# Contributing to AKIR-Framework

Vielen Dank für dein Interesse, AKIR zu verbessern! Um eine hohe Qualität der Sicherheitsfeatures zu gewährleisten, beachte bitte die folgenden Richtlinien.

## Code of Conduct
Wir legen Wert auf eine respektvolle und konstruktive Zusammenarbeit.

## Wie du beitragen kannst
1. **Security Vulnerabilities:** Falls du eine Schwachstelle im Framework findest, öffne bitte kein öffentliches Issue. Kontaktiere uns stattdessen privat (siehe Security Policy).
2. **Bug Reports:** Nutze die GitHub Issues und beschreibe das Problem sowie deine Systemumgebung (Windows Version, Build-Nr.).
3. **Pull Requests:**
   - Stelle sicher, dass alle Unit-Tests in der CI-Pipeline grün sind.
   - Neue Features müssen eine Dokumentation im `/docs` Ordner enthalten.
   - Kernel-relevanter Code muss strengen Performance-Checks unterzogen werden.

## Coding Standards
- C++20 Standard.
- Variable Benennung nach CamelCase (Agent) und PascalCase (Kernel).
- Kommentare müssen das "Warum" hinter einer Logik erklären, nicht nur das "Was".
