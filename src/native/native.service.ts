/* eslint-disable @typescript-eslint/no-unsafe-member-access */
import { Injectable } from '@nestjs/common';
const addon = require('../../build/Release/addon');

@Injectable()
export class NativeService {
  private threadCount = 0;
  private readonly maxThreads = 3; // Asegúrate de que maxThreads sea 3
  private isBlocked = false;

  startLoops(): string {
    if (this.isBlocked) {
      return 'Procesos ya iniciados';
    }

    if (this.threadCount >= this.maxThreads) {
      this.isBlocked = true;
      return 'Máximo de hilos alcanzado';
    }

    this.threadCount += 3; // Incrementa el contador de hilos

    addon.startLoops((err: any, result: string) => {
      if (err) {
        console.error(err);
      } else {
        console.log(result); // "Loop completed"
      }
    });

    return 'Loops started';
  }

  pauseLoop(loopNumber: number, pause: boolean): string {
    return addon.pauseLoop(loopNumber, pause);
  }

  getIteration(loopNumber: number): { iteration: number; threadId: string; pid: number } {
    return addon.getIteration(loopNumber);
  }

  getPIDs(): number[] {
    return addon.getPIDs();
  }
}