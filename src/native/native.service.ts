/* eslint-disable @typescript-eslint/no-unsafe-member-access */
import { Injectable, InternalServerErrorException } from '@nestjs/common';
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

  getIteration(loopNumber: number): { iteration: number; threadId: string; pid: number } {
    return addon.getIteration(loopNumber);
  }

  getPIDs(): number[] {
    return addon.getPIDs();
  }

  resetIteration(loopNumber: number): void {
    addon.resetIteration(loopNumber);
  }

  pauseIteration(loopNumber: number): string {
    if (typeof loopNumber !== 'number') {
      throw new TypeError('A number was expected');
    }
    const result = addon.pauseIteration(loopNumber);
    return result.message;
  }

  resumeIteration(loopNumber: number): string {
    if (typeof loopNumber !== 'number') {
      throw new TypeError('A number was expected');
    }
    const result = addon.resumeIteration(loopNumber);
    return result.message;
  }

}