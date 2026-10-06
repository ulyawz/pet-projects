import requests
from bs4 import BeautifulSoup

def scrape_website(url):
    response = requests.get(url)
    if response.status_code == 200:
        soup = BeautifulSoup(response.content, "html.parser")
        return soup
    else:
        print(f"Failed to retrieve the webpage. Status code: {response.status_code}")
        return None

def save_data_to_file(data, filename):
    with open(filename, "w", encoding="utf-8") as file:
        file.write(data)

def main():
    
    url = "https://people.onliner.by/2026/07/04/serialy-i-filmy-iyulya-2026"  
    soup = scrape_website(url)
    
    if soup:
          all_headings = soup.find_all(['h1', 'h2', 'h3', 'h4', 'h5', 'h6'])
          if all_headings:
            print(f"\nВсего найдено заголовков: {len(all_headings)}")
            data = "\n".join([h.get_text(strip=True) for h in all_headings])
            save_data_to_file(data, "headings_all.txt")
            print("Данные сохранены в headings_all.txt")
          else:
            print("Заголовков не найдено. Проверим другие элементы...")
          paragraphs = soup.find_all("p")
          if paragraphs:
                print(f"Найдено абзацев: {len(paragraphs)}")
                data = "\n".join([p.get_text(strip=True) for p in paragraphs])
                save_data_to_file(data, "paragraphs.txt")
                print("Все абзацы сохранены в paragraphs.txt")
if __name__ == "__main__":
    main()