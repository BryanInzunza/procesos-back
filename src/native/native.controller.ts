import { Controller, Get, Param, ParseIntPipe } from '@nestjs/common';
import { NativeService } from './native.service';

@Controller('native')
export class NativeController {
  constructor(private readonly nativeService: NativeService) {}

  @Get('start-loops')
  startLoops(): { message: string } {
    const message = this.nativeService.startLoops();
    return { message };
  }

  @Get('iteration/:loopNumber')
  getIteration(@Param('loopNumber', ParseIntPipe) loopNumber: number): {
    iteration: number;
    threadId: string;
    pid: number;
  } {
    return this.nativeService.getIteration(loopNumber);
  }

  @Get('pids')
  getPIDs(): number[] {
    return this.nativeService.getPIDs();
  }
}
