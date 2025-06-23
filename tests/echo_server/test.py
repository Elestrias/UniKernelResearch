import socket
import time

HOST = "127.0.0.1"
PORT = 8080
TEST_CASES = [10]
results = []

def worker(num_requests):
    MESSAGE = "Your message here\n" * 100000
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    total_sent = 0
    total_received = 0
    
    start_time = time.perf_counter()
    
    for _ in range(num_requests):
        sock.sendall(MESSAGE.encode('utf-8'))
        total_sent += len(MESSAGE)
        
        received = 0
        while received < len(MESSAGE):
            chunk = sock.recv(1024)
            if not chunk:
                break
            received += len(chunk)
        total_received += received
        if len(MESSAGE) < 10**5:
            MESSAGE = MESSAGE + MESSAGE
    
    sock.close()
    end_time = time.perf_counter()
    
    results.append({
        'requests': num_requests,
        'time': end_time - start_time,
        'sent': total_sent,
        'received': total_received
    })

if __name__ == "__main__":
    threads = []
    results = []
    
    for num_requests in TEST_CASES:
        worker(num_requests)
    
    for result in results:
        total_time = result['time']
        total_sent = result['sent']
        total_received = result['received']
        
        print(f"\nРезультаты для {result['requests']} запросов:")
        print(f"Общее время: {total_time:.2f} сек")
        print(f"Отправлено: {total_sent / (1024*1024):.2f} MiB")
        print(f"Получено: {total_received / (1024*1024):.2f} MiB")
        print(f"Скорость отправки: {(total_sent * 8) / (total_time * 1e6):.2f} Mbps")
        print(f"Скорость приёма: {(total_received * 8) / (total_time * 1e6):.2f} Mbps")
