#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>
#include <regex>

using namespace std;

// List of common technical skills
vector<string> skillsDatabase = {
    "C++", "Python", "Java", "JavaScript", "SQL", "Machine Learning", "AI",
    "Data Science", "Software Engineering", "Linux", "Git", "Django", "TensorFlow",
    "React", "Node.js", "Flutter", "Cybersecurity", "Blockchain"
};

// Function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Function to clean text (remove special characters)
string cleanText(const string& text) {
    string cleaned;
    for (char ch : text) {
        if (isalnum(ch) || ch == ' ' || ch == '\n') {
            cleaned += ch;
        }
    }
    return cleaned;
}

// Function to extract skills from resume
vector<string> extractSkills(const string& resumeText) {
    vector<string> foundSkills;
    string lowerResume = toLower(resumeText);

    for (const string& skill : skillsDatabase) {
        if (lowerResume.find(toLower(skill)) != string::npos) {
            foundSkills.push_back(skill);
        }
    }
    return foundSkills;
}

// Function to check experience in years using regex
int extractExperience(const string& resumeText) {
    regex expRegex(R"((\d+)\s*(years?|yrs?)\s*(of)?\s*(experience)?)", regex_constants::icase);
    smatch match;
    
    if (regex_search(resumeText, match, expRegex)) {
        return stoi(match[1]);
    }
    return 0; // Default if no experience found
}

// Function to read the resume from a file
string readResume(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    // Read the resume
    string resumeText = readResume("resume.txt");
    if (resumeText.empty()) {
        cerr << "Error: Resume file is empty or missing!" << endl;
        return 1;
    }

    // Clean the resume text
    resumeText = cleanText(resumeText);

    // Extract skills
    vector<string> skillsFound = extractSkills(resumeText);

    // Extract experience
    int experienceYears = extractExperience(resumeText);

    // Output results
    cout << "🔹 Resume Analysis Report 🔹\n\n";
    cout << "✅ Skills Found: ";
    if (!skillsFound.empty()) {
        for (const string& skill : skillsFound) {
            cout << skill << ", ";
        }
    } else {
        cout << "No relevant skills found!";
    }
    cout << "\n\n";

    cout << "📌 Experience Level: " << (experienceYears > 0 ? to_string(experienceYears) + " years" : "Not specified") << "\n";

    // Suggest missing skills
    cout << "\n💡 Suggested Skills to Learn: ";
    vector<string> missingSkills;
    for (const string& skill : skillsDatabase) {
        if (find(skillsFound.begin(), skillsFound.end(), skill) == skillsFound.end()) {
            missingSkills.push_back(skill);
        }
    }

    if (!missingSkills.empty()) {
        for (const string& skill : missingSkills) {
            cout << skill << ", ";
        }
    } else {
        cout << "You have all required skills!";
    }

    cout << "\n\n✅ Analysis Complete! 🚀\n";
    return 0;
}
